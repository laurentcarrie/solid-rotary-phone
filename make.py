from pathlib import Path
import subprocess
from subprocess import CompletedProcess
import traceback
import sys
import logging
from typing import List, Callable
import re
import click
import json

from util import check_type

logging.basicConfig(level=logging.INFO)

here = Path(__file__).parent


class Data:
    def __init__(self, song_files: List[Path], book_name: str, project_title: str, s3: str):
        self.song_files = song_files
        self.book_name = book_name
        self.project_title = project_title
        self.s3 = s3


def check_output(func: Callable[[Path, Path], CompletedProcess]):
    def inner(source: Path, target: Path):
        if not source.exists():
            logging.error(f'file does not exist : {source}')
            raise Exception(f'file does not exist : {source}')
        if not target.exists() or \
                target.stat().st_mtime < source.stat().st_mtime:
            p = func(source, target)
            if p.returncode != 0:
                logging.error(f'command returned code {p.returncode}')
                logging.error(f'{p.args}')
                logging.error(f'{p.stdout}')
                logging.error(f'{p.stderr}')

                raise Exception(f'command returned code {p.returncode}')
            if not target.exists():
                raise Exception(f'target {target} not  built')
        return
    return inner


@check_output
def make_png(source: Path, target: Path):
    p = subprocess.run(['lilypond', '-dbackend=eps', '-dresolution=600',
                        '--png', '--output', str(target.parent / target.stem),
                        str(source)])
    return p


@check_output
def make_midi(source: Path, target: Path):
    p = subprocess.run(['lilypond', '-dmidi-extension=midi',
                        '--output', str(target.parent / target.stem),
                        str(source)])
    return p


@check_output
def make_wav(source: Path, target: Path):
    p = subprocess.run(['fluidsynth', '--gain', '4', '-F', str(target),
                        '/usr/share/sounds/sf2/FluidR3_GM.sf2',
                        str(source)])
    return p


@check_output
def make_mp3(source: Path, target: Path):
    p = subprocess.run(['fluidsynth', '--gain', '4', '-F', str(target),
                        '/usr/share/sounds/sf2/FluidR3_GM.sf2',
                        "--audio-file-format","mp3",
                        str(source)])
    return p


def scan_rst(rst_file: Path) -> List[Path]:
    # ..image:: bohemian - like - you.png
    # `accords <wav/bohemian-like-you.wav> `_

    re_png = re.compile('\\.\\. image:: (.*)')
    re_other = re.compile('`.*<(.*?)>`_')

    ret = []
    with open(str(rst_file), 'r') as fin:
        for line in fin:
            # logging.info(line)
            result = re_png.match(line)
            if result is not None:
                link = result.group(1)
                logging.info(f'---- while scanning {rst_file} : <{link}>')
                ret.append(rst_file.parent / link)

            result = re_other.match(line)
            if result is not None:
                link = result.group(1)
                logging.info(f'---- while scanning {rst_file} : <{link}>')
                if not link.endswith('.mp3') and 'https://' not in str(link):
                    link = rst_file.parent / link
                    ret.append(link)

    return ret

# @todo : recursive scan


def scan_ly_ly(ly_file: Path) -> List[Path]:

    built_in_ly = [
        'predefined-guitar-fretboards.ly'
    ]

    # ..image:: bohemian - like - you.png
    r = re.compile(' *\\\\include *"(.*?)"')
    ret = []
    with open(str(ly_file), 'r') as fin:
        for line in fin:
            result = r.match(line)
            if result is not None:
                link = result.group(1)
                logging.info(f'---- while scanning {ly_file} : <{link}>')
                if link not in built_in_ly:
                    ret.append(ly_file.parent / link)
                    inner_deps = scan_ly_ly(ly_file.parent / link)
                    ret = ret + inner_deps

    return ret


def write_if_necessary(source: Path, target: Path):
    doit = False
    new_data = None
    if not target.exists():
        doit = True
    else:
        old_data = target.read_bytes()
        new_data = source.read_bytes()
        doit = old_data != new_data

    if doit:
        logging.info(f'... to copy : {target}')
        target.parent.mkdir(parents=True, exist_ok=True)
        if new_data is None:
            new_data = source.read_bytes()
        target.write_bytes(new_data)


def mount(srcfiles: List[Path], source_dir: Path, build_dir: Path) -> List[Path]:
    if not build_dir.exists():
        build_dir.mkdir()
    (build_dir / '_static').mkdir(exist_ok=True)
    (build_dir / '_static' / 'css').mkdir(exist_ok=True)
    ret = []
    for source in srcfiles:
        logging.info(f'mount {source}')
        target = build_dir / source.relative_to(source_dir)
        write_if_necessary(source, target)
        deps = scan_rst(source)
        ret = ret + deps
        for png in deps:
            ly = png.parent / (png.stem + '.ly')
            target: Path = build_dir / ly.relative_to(source_dir)
            write_if_necessary(ly, target)

            for ly_ly in scan_ly_ly(ly):
                target: Path = build_dir / ly_ly.relative_to(source_dir)
                target.write_text(ly_ly.read_text())

    return ret


def copy_to_s3(html_build_dir: Path, dest: str):

    p = subprocess.run([
        'aws', 's3', 'cp',
        '--recursive', str(html_build_dir / 'html'),
        dest]
    )
    print('The exit code was: %d' % p.returncode)


def sync_with_s3(html_build_dir: Path, dest: str):

    p = subprocess.run([
        'aws', 's3', 'sync',
        str(html_build_dir / 'html'),
        dest]
    )
    print('The exit code was: %d' % p.returncode)


def rmdir_f(path: Path):
    if not path.exists():
        return
    for p in path.iterdir():
        if p.is_file():
            p.unlink()
        else:
            if p.is_dir():
                rmdir_f(p)
                p.rmdir()
            else:
                raise Exception(f'not a file or a dir : {p}')


def beautify_ly(root: Path):
    check_type(root,Path)
    for f in root.iterdir():
        if f.is_file() and f.suffix == '.ly':
            outfile = f.with_suffix('.lytmp')
            p = subprocess.run(['ly', 'reformat;write', '-o', str(outfile), str(f)])
            if p.returncode != 0:
                logging.error(p.args)
                raise Exception(p.args)
            new_data = outfile.read_text()
            old_data = f.read_text()
            if new_data != old_data:
                logging.info(f'reformated : {f}')
                f.write_text(new_data)
        if f.is_dir():
            beautify_ly(f)


def get_all_rst_files(root: Path):
    ret = []
    for f in root.iterdir():
        if f.is_file() and f.suffix == '.rst':
            ret.append(f)
        if f.is_dir():
            ret = ret + get_all_rst_files(f)
    return ret


def read_json_definition(json_file: Path, source_dir: Path) -> Data:
    check_type(json_file,Path)
    if not json_file.exists() :
        raise FileExistsError(f"{str(json_file)}")
    with json_file.open('r') as f:
        data = json.load(f)
        song_files = [source_dir / Path(s) for s in data['songs']]
        book_name = data['book_name']
        return Data(song_files=song_files, book_name=book_name, project_title=data['project_title'],
                    s3=data['s3'])


def make_conf_py(data_conf: Data, source_dir: Path, build_dir: Path):
    text = (Path(source_dir) / 'conf.template.py').read_text()
    text = text.replace('$project_title$', data_conf.project_title)
    (Path(build_dir) / 'conf.py').write_text(text)


def make_index_rst(data_conf: Data, source_dir: Path, build_dir: Path):
    text = (Path(source_dir) / 'index.template.rst').read_text()
    song_files = ''
    for s in data_conf.song_files:
        song_files = song_files + \
            f"   {s.relative_to(source_dir).with_suffix('')}" + '\n'
    text = text.replace('$song_files$', song_files)
    text = text.replace('$title$', data_conf.project_title)
    (Path(build_dir) / 'index.rst').write_text(text)


@click.command()
@click.option('--clean-first', default=False, is_flag=True,
              help='clean build directories')
@click.option('--s3', default=False, is_flag=True,help='upload to s3')
@click.option('--reformat', default=False, is_flag=True, help='reformat ly files' )
@click.option('--build', default=False, is_flag=True, help='build')
@click.option('--book', required=True,help='name of the book')
def main(s3, clean_first, reformat, build, book):
    try:
        source_dir = here / 'source'

        data_conf = read_json_definition(Path(book), source_dir=source_dir)

        logging.info(f'source_dir : {source_dir}')
        build_dir = here / 'build' / data_conf.book_name
        html_build_dir = here / 'html-build' / data_conf.book_name
        logging.info(f'source_dir : {build_dir}')

        build_dir.mkdir(parents=True, exist_ok=True)
        html_build_dir.mkdir(parents=True, exist_ok=True)

        if reformat:
            beautify_ly(source_dir)

        if clean_first:
            rmdir_f(build_dir)
            rmdir_f(html_build_dir)

        if build:
            mount([
                source_dir / '_static' / 'css' / 'custom.css'
            ],
                source_dir, build_dir)
            make_conf_py(data_conf=data_conf, source_dir=source_dir, build_dir=build_dir)
            make_index_rst(data_conf=data_conf,
                           source_dir=source_dir, build_dir=build_dir)
            ret = mount(data_conf.song_files, source_dir, build_dir)
            ret = [build_dir / f.relative_to(source_dir) for f in ret]

            for f in ret:
                if f.suffix == '.png':
                    make_png(source=f.parent / (f.stem + '.ly'), target=f)
                if f.suffix == '.wav':
                    make_midi(source=f.parent / (f.stem + '.ly'),
                              target=f.parent / (f.stem + '.midi'))
                    make_wav(source=f.parent / (f.stem + '.midi'), target=f)
                if f.suffix == '.mp3':
                    make_midi(source=f.parent / (f.stem + '.ly'),
                              target=f.parent / (f.stem + '.midi'))
                    make_mp3(source=f.parent / (f.stem + '.midi'), target=f)

            p = subprocess.run(['sphinx-build', '-M', 'html',
                                str(build_dir), str(html_build_dir)])
            print('The exit code was: %d' % p.returncode)

            p = subprocess.run(['sphinx-build', '-M', 'latexpdf',
                                str(build_dir), str(html_build_dir)])
            print('The exit code was: %d' % p.returncode)

            for f in ret:
                if f.suffix == '.wav':
                    write_if_necessary(f, html_build_dir / 'html'
                                       / f.relative_to(build_dir))

        if s3:
            if data_conf.s3 is None:
                raise Exception('no s3 destination')
            sync_with_s3(html_build_dir, data_conf.s3)

    except Exception as e:
        logging.error(e)
        traceback.print_exc(file=sys.stdout)


if __name__ == '__main__':
    main()
