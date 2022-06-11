.PHONY:  all clean delivery pdf
.DEFAULT: all
project=incubus-drive

include $(CURDIR)/../../../macros/Makefile

$(project).pdf : song.tex lyrics.tex body.tex grille.tex
	bash $(buildtex) $@ $^

pdf : $(project).pdf

clean:
	rm -rf build
	rm -rf *.pdf