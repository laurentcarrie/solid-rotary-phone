project=natalie-umbrogila-torn

include $(CURDIR)/../../../macros/Makefile


$(project).pdf : song.tex lyrics.tex grille.tex body.tex
	bash $(buildtex) $@ $^

pdf : $(project.pdf)

clean :
	rm -rf build
	rm -rf *.pdf