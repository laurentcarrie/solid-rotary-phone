#!/bin/bash


#books="garenne pscl ultimate-chorus"

books="work"


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
  tmpdir=zik
  rm -rf $tmpdir
  mkdir $tmpdir
  cp source/welcome.html $tmpdir/index.html
  for b in $books ; do
    echo $b
    rm -rf html-build/$b/doctrees
    rm -rf html-build/$b/latex
    cp -R html-build/$b $tmpdir/$b
    #mkdir -p /run/user/1000/gvfs/mtp\:host=SAMSUNG_SAMSUNG_Android_R9HN9011YHJ/Phone/Download/zik/$b
    #cp -R html-build/$b/html /run/user/1000/gvfs/mtp:host=SAMSUNG_SAMSUNG_Android_R9HN9011YHJ/Phone/Download/zik/$b | true
    #rsync -vr html-build/$b/html /run/user/1000/gvfs/mtp\:host\=SAMSUNG_SAMSUNG_Android_R9HN9011YHJ/Phone/Download/zik/$b/
  done

  #rsync -vr $tmpdir /run/user/1000/gvfs/'mtp:host=SAMSUNG_SAMSUNG_Android_R9HN9011YHJ'/Phone/Download/

  find $tmpdir -type f | while read f ; do
    echo $f
    target=/run/user/1000/gvfs/mtp:host=SAMSUNG_SAMSUNG_Android_R9HN9011YHJ/Phone/Download/$f
    gio mkdir -p $(dirname $target) | true
    gio copy $f $target
    #(
    #  cd $(dirname $f) &&
    #  gio copy $(basename $f) /run/user/1000/gvfs/mtp:host=SAMSUNG_SAMSUNG_Android_R9HN9011YHJ/Phone/Download/$f
    #)
  done


  #cp source/welcome.html /run/user/1000/gvfs/mtp:host=SAMSUNG_SAMSUNG_Android_R9HN9011YHJ/Phone/Download/zik/index.html

}

configVolumePath=/home/laurent/work/solid-rotary-phone/html-build/

function start_web_server {

  docker volume create --driver local \
    --opt type=none \
    --opt device=$configVolumePath \
    --opt o=bind \
    config_vol




  docker rm --force nginx
  cp source/welcome.html html-build/index.html
  docker run \
    --name nginx \
    -p 8080:80 \
    --volume config_vol:/usr/share/nginx/html \
    nginx:latest &
}


case $1 in
songs)
  shift
  make_clean
  for b in $books; do
    make_songs $b
  done
  start_web_server
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
  make_docker
  make_aws
  ;;
s3)
  sync_mp3s
  ;;
phone)
  make_phone
  ;;
nginx)
  start_web_server
  ;;
*)
  echo "no such command : $1"
esac
