#!/bin/sh

set -e
set -x


texfile=song.tex
project=$1

name=$(echo $(basename $texfile) | sed "s/\..*$//")

mkdir -p build
cp *.tex build/.
cat song.tex | sed "s#input{../../../macros#input{../../../../macros#" > build/song.tex

while true ; do
    (
    cd build
     lualatex $texfile
    )
    count=$(cat build/$name.log | grep "Rerun" | wc -l)
    echo "count is $count"
    if test $count -eq 0; then
      break
    fi
done
cp build/song.pdf $project.pdf
