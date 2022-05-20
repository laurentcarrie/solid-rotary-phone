#!/bin/sh

set -e
set -x

heredir=$(pwd)
macrodir=$(realpath $(dirname $0))

pdffile=$1
echo "buildtex.sh $pdffile"
project=$(echo $pdffile | sed "s/\..*//")

shift
texfiles=$*

printf "texfile is $texfiles\n"
mkdir -p build

for f in chords.tex macros.ly preamble.tex; do
  cp $macrodir/$f build/$f
done

tex_ext=lytex

for f in $texfiles; do
  echo "+++ f is $f"
  g=$(echo $f | sed "s/\.tex/.$tex_ext/")
  echo "+++ g is $g"
  if [[ "$f" =~ .*"ly" ]]; then
    echo "+++ $f is a ly file"
    cp $f build/$g
  fi

  if [[ "$f" =~ .*"tex".* ]]; then
    cp $f build/$g
    #if ! test  `grep "\\lilypondx" $f | wc -l ` -eq 0 ; then
    # echo "+++ +++ $f contains \\lilypond"
    # rm -rf tmp-pond
    # lilypond-book --output tmp-pond $f
    #mv tmp-pond/* build/.
    #fi
    echo "+++ +++ $g is a tex file"
    cat build/$g |
      sed -E "s#includegraphics(.*?)\{(.*)\}#includegraphics\1{$heredir/\2}#" |
      sed -E "s#input\{(.*?).tex\}#input{$heredir/build/\1.$tex_ext}#" |
      sed -E "s#lilypondfile(.*?)\{(.*?).ly\}#lilypondfile\1{$heredir/build/\2.ly}#" |
      sed -E "s#input\{.*/macros/(.*?).$tex_ext#input{\1.tex#" \
        >build/$g.tmp
    mv build/$g.tmp build/$g
  fi
done

(
  cd build
  rm -rf toto
  lilypond-book --output=toto --format=latex --latex-program=lualatex --pdf song.$tex_ext
  rm -f song.tex
  mv toto/* .
)

while true; do
  (cd build && lualatex song.tex)
  count=$(cat build/song.log | grep "Rerun" | wc -l)
  echo "count is $count"
  if test $count -eq 0; then
    break
  fi
done

echo "pwd is $PWD"

cp build/song.pdf $project.pdf
