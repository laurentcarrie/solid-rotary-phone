.PHONY:  all clean delivery pdf
.DEFAULT: all
project=david-bowie-modern-love


include $(CURDIR)/../../../macros/Makefile

$(project).pdf : song.tex lyrics.tex body.tex grille.tex intro.ly intro_layout.ly
	bash $(buildtex) $@ $^

pdf : $(project).pdf

intro.midi : intro_midi.ly intro.ly
	lilypond -dmidi-extension=midi --output intro intro_midi.ly

intro.wav : intro.midi
	fluidsynth --gain 4 -F $@ /usr/share/sounds/sf2/FluidR3_GM.sf2 $<

wav : intro.wav

clean :
	rm -rf build *.pdf *.wav *.midi

all : clean wav pdf

