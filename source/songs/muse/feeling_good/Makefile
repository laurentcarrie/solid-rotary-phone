.PHONY:  all clean delivery pdf
.DEFAULT=delivery
project=muse-feeling-good

include $(CURDIR)/../../../macros/Makefile


$(project).pdf : song.tex lyrics.tex grille.tex body.tex build/solo_png.png
	bash $(buildtex) $@ $^

build/solo_png.png : solo_png.ly solo.ly
	bash $(buildpngly) $^

build/solo_midi.midi : solo_midi.ly solo.ly
	bash $(buildpngly) $^

pdf : $(project).pdf
