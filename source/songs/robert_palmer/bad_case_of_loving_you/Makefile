.PHONY:  all clean delivery pdf
.DEFAULT: all
project=robert-palmer-bad-case-of-loving-you

include $(CURDIR)/../../../macros/Makefile

$(project).pdf : song.tex lyrics.tex grille.tex body.tex
	bash $(buildtex) $@ $^

pdf : $(project).pdf

clean :
	rm -rf build
	rm -rf *.pdf