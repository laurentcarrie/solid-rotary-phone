.PHONY:  all clean delivery
.DEFAULT: all
project=matmatah-au-conditionnel


include $(CURDIR)/../../../macros/Makefile



$(project).pdf : song.tex lyrics.tex grille.tex
	bash $(buildtex) song.tex
	mv song.pdf $(project).pdf

#solo_png.png : solo_png.ly solo.ly
	 #lilypond -dbackend=eps -dno-gs-load-fonts -dinclude-eps-fonts --png --output $(basename $@) $<



all: $(project).pdf

