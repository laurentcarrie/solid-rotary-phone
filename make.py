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
logging.info(f'source_dir : {build_dir}')


def check_output(func):
    def inner(args):
        target = func(args)
        if not target.exists():
            raise Exception(f'target {target} not  built')
        return target
    return inner


@check_output
def make_png(input_file: Path) -> Path:
    name = input_file.name
    logging.info(name)
    target: Path = build_dir / (input_file.stem + '.png')
    p = subprocess.run(['lilypond', '-dbackend=eps', '-dresolution=600',
                        '--png', '--output', str(target),
                        str(source_dir / input_file)])
    print('The exit code was: %d' % p.returncode)

    return target


def scan_rst_png(rst_file: Path) -> List[Path]:
    # ..image:: bohemian - like - you.png
    r = re.compile('\\.\\. image:: (.*)')
    ret = []
    with open(str(rst_file), 'r') as fin:
        for line in fin:
            # logging.info(line)
            result = r.match(line)
            if result is not None:
                link = result.group(1)
                logging.info(f'{line} ; <{link}>')
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
                logging.info(f'matched in ly : {line} ; <{link}>')
                if link not in built_in_ly:
                    ret.append(ly_file.parent / link)

    return ret


def mount(srcfiles: List[Path]):
    for source in srcfiles:
        target = build_dir / source.relative_to(source_dir)
        logging.info(f'{target}')
        target.write_text(source.read_text())
        for png in scan_rst_png(source):
            ly = png.parent / (png.stem + '.ly')
            target: Path = build_dir / ly.relative_to(source_dir)
            target.write_text(ly.read_text())

            for ly_ly in scan_ly_ly(ly):
                target: Path = build_dir / ly_ly.relative_to(source_dir)
                target.write_text(ly_ly.read_text())


if __name__ == '__main__':
    try:
        f: Path = source_dir / 'bohemian-like-you.rst'

        mount([f])

    except Exception as e:
        logging.error(e)
        traceback.print_exc(file=sys.stdout)
