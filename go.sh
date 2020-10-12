#!/bin/bash

set -e
set -x

rm -rf build

lilypond -dbackend=eps -dresolution=600 --png source/bohemian-like-you.ly
cp bohemian-like-you.png source/.

make latexpdf
make html
aws s3 cp --recursive build/html/ s3://s3-lolo-web/html
