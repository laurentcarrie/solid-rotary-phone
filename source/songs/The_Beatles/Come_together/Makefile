project=beatles-come-together

include $(CURDIR)/../../../macros/Makefile


$(project).pdf : song.tex lyrics.tex grille.tex build/solo_final_png.png build/solo_1_png.png body.tex
	bash $(buildtex) $@ $^

build/solo_1_png.png : solo_1_png.ly solo_1.ly
	bash $(buildpngly) $^

build/solo_final_png.png : solo_final_png.ly solo_final.ly
	bash $(buildpngly) $^
