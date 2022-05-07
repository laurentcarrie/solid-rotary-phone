.PHONY:  all clean delivery
.DEFAULT: all
project=natalie-umbrogila-torn

include $(CURDIR)/../../../macros/Makefile





$(project).pdf : song.tex lyrics.tex grille.tex
	bash $(buildtex) song.tex
	mv song.pdf $(project).pdf

solo_png.png : solo_png.ly solo.ly
	 lilypond -dbackend=eps -dno-gs-load-fonts -dinclude-eps-fonts --png --output $(basename $@) $<

intro_png.png : intro_png.ly intro.ly
	 lilypond -dbackend=eps -dno-gs-load-fonts -dinclude-eps-fonts --png --output $(basename $@) $<



