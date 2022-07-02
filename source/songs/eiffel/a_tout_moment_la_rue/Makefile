.PHONY:  all clean delivery pdf
.DEFAULT: all
project=eiffel-a-tout-moment-la-rue

include $(CURDIR)/../../../macros/Makefile

$(project).pdf : song.tex lyrics.tex grille.tex body.tex solo_png.ly solo.ly
	bash $(buildtex) $@ $^

pdf : $(project).pdf

clean :
	rm -rf build
	rm -rf *.pdf
	rm -rf *.midi *.wav

all : pdf solo.wav

solo.midi : solo_midi.ly solo.ly
	lilypond -dmidi-extension=midi --output solo solo_midi.ly

solo.wav : solo.midi
	fluidsynth --gain 4 -F $@ /usr/share/sounds/sf2/FluidR3_GM.sf2 $<