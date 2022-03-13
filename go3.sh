#!/usr/bin/env bash

set -e
set -x

rm -rf build



./cxx/cmake-build-debug/solid_rotary_phone /Users/laurent/work/solid-rotary-phone/source/ /Users/laurent/work/solid-rotary-phone/build work

afplay ~/work/solid-rotary-phone/build/deep_purple/smoke_on_the_water/solo_midi.wav

