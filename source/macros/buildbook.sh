#!/bin/sh

set -e
set -x

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
cat $texfile \
  | sed -E "s#input\{(.*?)/build/body.tex\}#input{$heredir/\1/build/body.lytex}#" \
  | sed -E "s#input\{.*/macros#input{$macropath#" \
    >build/$lytexfile

  (
    cd build
    rm -rf toto
    lilypond-book --output=toto --pdf --format=latex --latex-program=lualatex $lytexfile || true
    rm -f $texfile
    mv toto/* .
  )

while true; do
  (
    cd build
    lualatex $texfile
  )
  count=$(cat build/$logfile | grep "Rerun" | wc -l)
  echo "count is $count"
  if test $count -eq 0; then
    break
  fi
done
cp build/$pdffile $pdffile
