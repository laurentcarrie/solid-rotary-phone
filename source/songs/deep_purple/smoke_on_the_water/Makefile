.PHONY:  all clean delivery pdf
.DEFAULT: all
project=deep-purple-smoke-on-the-water

include $(CURDIR)/../../../macros/Makefile

$(project).pdf : song.tex lyrics.tex grille.tex build/solo_png.png build/intro_png.png
	bash $(buildtex) $(project)

build/solo_png.png : solo_png.ly solo.ly
	bash $(buildpngly) $^

build/intro_png.png : intro_png.ly intro.ly
	bash $(buildpngly) $^

pdf : $(project).pdf
