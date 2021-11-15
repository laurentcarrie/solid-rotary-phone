#!/bin/bash

set -e
set -x

source .venv/bin/activate

here=$(dirname $(realpath $0))

function make_clean {
  rm -rf build
  rm -rf html-build


}

function make_songs {
#make $1


find . -name "*.lytmp" | while read f ; do rm $f ; done

python make.py --reformat --build --book $here/source/$1.json

find . -name "*.lytmp" | while read f ; do rm $f ; done

# pour créer des .mid à partir de .ly
#         lilypond -dmidi-extension=mid bohemian-like-you.ly
# pour creer des .wav à partir de .mid
#         sudo apt install fluidsynth fluid-soundfont-gm
#         fluidsynth -F out.wav /usr/share/sounds/sf2/FluidR3_GM.sf2 bohemian-like-you.mid
# pour jouer
#         sudo apt install sox
#         play bohemian-like-you.wav


}

function sync_mp3s {

  aws s3 sync $HOME/Music/work-mp3 s3://s3-lolo-web/zik/work-mp3/
  #aws s3 cp --recursive $HOME/Music/work-mp3 s3://s3-lolo-web/zik/work-mp3/
}



function make_docker {

  docker rm --force songs
  docker build -t songs .
  docker run -d --rm -p 8080:80 --name songs songs

}


function make_aws {

  aws lightsail push-container-image --region eu-west-3 --service-name chansons --label chansons --image songs:latest

}


function make_phone {

  cp -R html-build /run/user/1000/gvfs/mtp:host=SAMSUNG_SAMSUNG_Android_R9HN9011YHJ/Phone/Download/.

}


case $1 in
songs)
  shift
  make_clean
  make_songs $*
  ;;
local)
  shift
  make_clean
  make_songs $*
  make_docker
  ;;
aws)
  shift
  make_clean
  make_songs pscl
  make_songs uc
  make_songs garenne
  make_songs uc
  make_docker
  make_aws
  ;;
s3)
  sync_mp3s
  ;;
phone)
  make_phone
  ;;
*)
  echo "no such command : $1"
esac


