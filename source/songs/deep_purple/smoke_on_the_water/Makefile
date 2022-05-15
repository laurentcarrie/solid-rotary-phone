.PHONY:  all clean delivery pdf
.DEFAULT: all
project=deep-purple-smoke-on-the-water

include $(CURDIR)/../../../macros/Makefile

$(project).pdf : song.tex lyrics.tex body.tex grille.tex build/solo_png.png build/intro_png.png
	bash $(buildtex) $@ $^

build/solo_png.png : solo_png.ly solo.ly
	bash $(buildpngly) $^

build/intro_png.png : intro_png.ly intro.ly
	bash $(buildpngly) $^

pdf : $(project).pdf


test.pdf : toto/test.tex
	cd toto && lualatex test.tex && mv test.pdf ..

toto/test.tex : test.tex
	lilypond-book --output toto --pdf --latex-program=lualatex test.tex
