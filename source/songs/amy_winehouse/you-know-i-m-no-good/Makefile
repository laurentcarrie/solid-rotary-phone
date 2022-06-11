project=amy-winehouse-you-know-i-m-no-good
include $(CURDIR)/../../../macros/Makefile


$(project).pdf : song.tex body.tex lyrics.tex grille.tex break_png.ly break.ly
	bash $(buildtex) $@ $^


pdf : $(project).pdf

clean :
	rm -rf build
	rm -rf *.pdf

