#!/bin/sh

set -e
set -x

texfile=$1

name=$(echo $(basename $texfile) | sed "s/\..*$//")

while true ; do
  pdflatex $texfile
  count=`cat $name.log | grep "Rerun" | wc -l `
  echo "count is $count"
  if test $count -eq 0 ; then
    break ;
  fi
done

