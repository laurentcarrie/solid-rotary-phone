.PHONY:  all clean delivery
.DEFAULT=delivery
project=muse-feeling-good

include $(CURDIR)/../../../macros/Makefile




$(project).pdf : song.tex lyrics.tex grille.tex solo_png.png
	bash $(buildtex) song.tex
	mv song.pdf $(project).pdf

solo_png.png : solo_png.ly solo.ly
	 lilypond -dbackend=eps -dno-gs-load-fonts -dinclude-eps-fonts --png --output $(basename $@) $<


solo_midi.midi : solo_midi.ly solo.ly
	lilypond -dmidi-extension=midi --output solo_midi solo_midi.ly

all : solo_midi.midi