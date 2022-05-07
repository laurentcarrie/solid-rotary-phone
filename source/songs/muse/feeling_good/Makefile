.PHONY:  all clean delivery
.DEFAULT=delivery
project=muse-feeling-good

include $(CURDIR)/../../../macros/Makefile




$(project).pdf : song.tex lyrics.tex grille.tex solo_png.png
	bash $(buildtex) song.tex
	mv song.pdf $(project).pdf

solo_png.png : solo_png.ly solo.ly
	 lilypond -dbackend=eps -dno-gs-load-fonts -dinclude-eps-fonts --png --output $(basename $@) $<
