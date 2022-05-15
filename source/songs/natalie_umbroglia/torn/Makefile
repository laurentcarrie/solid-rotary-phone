.PHONY:  all clean delivery pdf
.DEFAULT: all
project=natalie-umbrogila-torn

include $(CURDIR)/../../../macros/Makefile


$(project).pdf : song.tex lyrics.tex grille.tex
	bash $(buildtex) $(project)


pdf : $(project).pdf
