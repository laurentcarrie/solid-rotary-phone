#!/bin/sh

set -e
set -x

heredir=$(pwd)

pdffile=$1
project=`echo $pdffile | sed "s/\..*//"`

shift
texfiles=$*

mkdir -p build
cp *.tex build/.


for f in $texfiles ; do
  if [[ "$f" =~ .*"tex".* ]] ; then
    echo ">>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>> $f"
    cp $f build/$f
    sed -i "s#input{../../../macros#input{../../../../macros#" build/$f
    sed -i  -E "s#includegraphics(.*?)\{(.*?)\}#includegraphics\1{$heredir/\2}#" build/$f
    sed -i -E "s#input\{(.*?)\}#input{$heredir/build/\1}#" build/$f
  fi
done


while true; do
  (
    cd build
    lualatex song.tex
  )
  count=$(cat build/$song.log | grep "Rerun" | wc -l)
  echo "count is $count"
  if test $count -eq 0; then
    break
  fi
done
cp build/song.pdf $project.pdf
