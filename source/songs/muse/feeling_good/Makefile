.PHONY:  all clean delivery pdf
.DEFAULT=delivery
project=muse-feeling-good

include $(CURDIR)/../../../macros/Makefile


$(project).pdf : song.tex lyrics.tex body.tex grille.tex body.tex solo_png.ly solo.ly
	bash $(buildtex) $@ $^



pdf : $(project).pdf

