#!/bin/bash

set -e
set -x

source .venv/bin/activate

here=$(dirname $(realpath $0))

function make_clean {
  rm -rf html
  rm -rf html-build


}

function make_songs {
#make $1
python make.py --reformat --build --book $here/source/$1.json

# pour créer des .mid à partir de .ly
#         lilypond -dmidi-extension=mid bohemian-like-you.ly
# pour creer des .wav à partir de .mid
#         sudo apt install fluidsynth fluid-soundfont-gm
#         fluidsynth -F out.wav /usr/share/sounds/sf2/FluidR3_GM.sf2 bohemian-like-you.mid
# pour jouer
#         sudo apt install sox
#         play bohemian-like-you.wav


}



function make_docker {

  docker rm --force songs
  docker build -t songs .
  docker run -d --rm -p 8080:80 --name songs songs

}


function make_aws {

  aws lightsail push-container-image --region eu-west-3 --service-name songs --label songs --image lc-songs:latest

}


case $1 in
songs)
  shift
  make_songs $*
  ;;
local)
  shift
  make_songs $*
  make_docker
  ;;
aws)
  shift
  make_songs pscl
  make_songs uc
  make_songs garenne
  make_docker
  make_aws
  ;;
*)
  echo "no such command : $1"
esac


