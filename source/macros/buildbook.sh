#!/bin/sh

set -e
set -x

texfile=$1
pdffile=$(echo $texfile | sed "s#.tex#.pdf#")
logfile=$(echo $texfile | sed "s#.tex#.log#")
heredir=$(pwd)

name=book

rm -rf build
mkdir -p build/
cat $texfile | sed "s#input{../macros#input{../../macros#" |
  sed -E "s#input\{(.*)/build/body\}#input{../\1/build/body}#" \
    >build/$texfile

while true; do
  (
    cd build
    #lualatex $texfile
    lilypond-book --output=out --pdf --latex-prog=lualatex song.tex
  )
  count=$(cat build/$logfile | grep "Rerun" | wc -l)
  echo "count is $count"
  if test $count -eq 0; then
    break
  fi
done
cp build/$pdffile $pdffile
