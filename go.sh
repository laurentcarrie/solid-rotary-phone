#!/bin/bash

set -e
set -x

source venv/bin/activate

here=$(dirname $(realpath $0))

#make $1
python make.py --reformat --build --book $here/source/pscl.json

# pour créer des .mid à partir de .ly
#         lilypond -dmidi-extension=mid bohemian-like-you.ly
# pour creer des .wav à partir de .mid
#         sudo apt install fluidsynth fluid-soundfont-gm
#         fluidsynth -F out.wav /usr/share/sounds/sf2/FluidR3_GM.sf2 bohemian-like-you.mid
# pour jouer
#         sudo apt install sox
#         play bohemian-like-you.wav
