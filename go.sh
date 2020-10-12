#!/bin/bash

set -e
set -x

rm -rf build

lilypond_files="bohemian-like-you scar-tissue"

for f in $lilypond_files ; do
  lilypond -dbackend=eps -dresolution=600 --png source/$f.ly
  cp $f.png source/.
done

make latexpdf
make html
aws s3 cp --recursive build/html/ s3://s3-lolo-web/html
