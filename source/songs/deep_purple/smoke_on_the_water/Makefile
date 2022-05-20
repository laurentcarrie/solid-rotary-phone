.PHONY:  all clean delivery pdf
.DEFAULT: all
project=deep-purple-smoke-on-the-water

include $(CURDIR)/../../../macros/Makefile

$(project).pdf : song.tex lyrics.tex body.tex grille.tex  solo.ly intro_png.ly intro.ly
	bash $(buildtex) $@ $^

pdf : $(project).pdf


test.pdf : toto/test.tex
	cd toto && lualatex test.tex && mv test.pdf ..

toto/test.tex : test.tex
	lilypond-book --output toto --pdf --latex-program=lualatex test.tex
