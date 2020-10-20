from pathlib import Path
import subprocess
import traceback
import sys
import logging
from typing import List
import re

logging.basicConfig(level=logging.INFO)

here = Path(__file__).parent

source_dir = here / 'source'
logging.info(f'source_dir : {source_dir}')
build_dir = here / 'build'
html_build_dir = here / 'html-build'
logging.info(f'source_dir : {build_dir}')
rst_sources = [source_dir / f for f in [
    'index.rst',
    'bohemian-like-you.rst',
    'scar-tissue.rst',
    'creep.rst'
]]


def check_output(func):
    def inner(source: Path, target: Path):
        if not target.exists() or \
                target.stat().st_mtime < source.stat().st_mtime:
            func(source, target)
            if not target.exists():
                raise Exception(f'target {target} not  built')
        return
    return inner


@check_output
def make_png(source: Path, target: Path):
    p = subprocess.run(['lilypond', '-dbackend=eps', '-dresolution=600',
                        '--png', '--output', str(target.parent/target.stem),
                        str(source)])
    print('The exit code was: %d' % p.returncode)

    return target


@check_output
def make_wav(source: Path, target: Path):
    p = subprocess.run(['fluidsynth', '-F', str(target),
                        '/usr/share/sounds/sf2/FluidR3_GM.sf2', str(source)])

    print('The exit code was: %d' % p.returncode)

    return target


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
                ret.append(rst_file.parent / link)

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

    return ret


def write_if_necessary(source, target):
    if not target.exists() or target.stat().st_mtime < source.stat().st_mtime:
        logging.info(f'... to copy : {target}')
        target.write_bytes(source.read_bytes())


def mount(srcfiles: List[Path]) -> List[Path]:
    if not build_dir.exists():
        build_dir.mkdir()
    (build_dir/'_static').mkdir(exist_ok=True)
    (build_dir/'_static'/'css').mkdir(exist_ok=True)
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


def copy_to_s3():
    p = subprocess.run([
        'aws', 's3', 'cp',
        '--recursive', str(html_build_dir/'html'),
        's3://s3-lolo-web/labandeapierrestephanecelinelaurent/html'])
    print('The exit code was: %d' % p.returncode)


if __name__ == '__main__':
    try:
        mount([source_dir/'conf.py', source_dir/'_static'/'css'/'custom.css'])
        ret = mount(rst_sources)
        ret = [build_dir/f.relative_to(source_dir) for f in ret]

        for f in ret:
            if f.suffix == '.png':
                logging.info(f'xxxxxxxxxxxxxxxxxx {f}')
                make_png(source=f.parent/(f.stem+'.ly'), target=f)
            if f.suffix == '.wav':
                logging.info(f'xxxxxxxxxxxxxxxxxx {f}')
                make_wav(source=f.parent/(f.stem+'.midi'), target=f)

        p = subprocess.run(['sphinx-build', '-M', 'html',
                            str(build_dir), str(html_build_dir)])
        print('The exit code was: %d' % p.returncode)

        for f in ret:
            if f.suffix == '.wav':
                write_if_necessary(f, html_build_dir/'html' /
                                   f.relative_to(build_dir))

        copy_to_s3()

    except Exception as e:
        logging.error(e)
        traceback.print_exc(file=sys.stdout)
