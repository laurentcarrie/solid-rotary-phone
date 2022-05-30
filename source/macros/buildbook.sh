#!/bin/sh

set -e
set -x

echo "YYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYY"

texfile=$1
echo "texfile is $texfile"
pdffile=$(echo $texfile | sed "s#.tex#.pdf#")
logfile=$(echo $texfile | sed "s#.tex#.log#")
lytexfile=$(echo $texfile | sed "s#.tex#.lytex#")
echo "lytexfile is $lytexfile"
echo "pwd is $(pwd)"
heredir=`echo $(pwd)`
echo "heredir is $heredir"
name=book

macropath=$(dirname $(realpath $0))

rm -rf build
mkdir -p build/

