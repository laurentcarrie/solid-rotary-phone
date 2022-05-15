.PHONY:  all clean delivery pdf
.DEFAULT: all
project=robert-palmer-bad-case-of-loving-you

include $(CURDIR)/../../../macros/Makefile

$(project).pdf : song.tex lyrics.tex grille.tex
	bash $(buildtex) $(project)

pdf : $(project).pdf

