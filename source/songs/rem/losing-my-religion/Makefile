project=rem-losing-my-religion
include $(CURDIR)/../../../macros/Makefile


$(project).pdf : song.tex body.tex lyrics.tex grille.tex intro_png.ly intro.ly
	bash $(buildtex) $@ $^


pdf : $(project).pdf

clean :
	rm -rf build
	rm -rf *.pdf
	rm -rf *.midi *.wav

all : pdf intro.wav

intro.midi : intro_midi.ly intro.ly
	lilypond -dmidi-extension=midi --output intro intro_midi.ly

intro.wav : intro.midi
	fluidsynth --gain 4 -F $@ /usr/share/sounds/sf2/FluidR3_GM.sf2 $<