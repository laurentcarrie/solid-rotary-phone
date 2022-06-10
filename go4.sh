#!/usr/bin/sh

set -e
set -x

(
rm -f solid_rotary_phone_make_chords ;
cd cxx && cmake . && make ;
)

./cxx/solid_rotary_phone_make_chords source/macros

rm -rf delivery

make  clean delivery -C source/songs
make  clean delivery -C source/books