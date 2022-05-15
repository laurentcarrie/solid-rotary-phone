#!/bin/sh

set -e
set -x


mkdir -p build

echo $*

macropath=$(realpath $PWD/../../../macros)

for i in $* ; do
  cat $i | sed "s#../../../../macros#$macropath#" > build/$i

done


source=$(echo $(basename $1) | sed "s/\..*$//")

shift
others=$*

cd build && lilypond -dbackend=eps -dno-gs-load-fonts -dinclude-eps-fonts --png --output $source $source




