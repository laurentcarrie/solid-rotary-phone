project=beatles-come-together

include $(CURDIR)/../../../macros/Makefile


$(project).pdf : song.tex lyrics.tex body.tex grille.tex solo_1_png.ly solo_1.ly solo_final.ly solo_final_png.ly
	bash $(buildtex) $@ $^

pdf : $(project).pdf
