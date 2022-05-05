.PHONY:  all clean delivery
.DEFAULT: all
project=deep-purple-smoke-on-the-water

texfiles=

clean:
	rm -rf *.wav *.png *.pdf *.aux *.log *.eps *.count *-systems.*



$(project).pdf : song.tex lyrics.tex grille.tex solo_png.png intro_png.png
	pdflatex song.tex
	pdflatex song.tex
	mv song.pdf $(project).pdf

solo_png.png : solo_png.ly solo.ly
	 lilypond -dbackend=eps -dno-gs-load-fonts -dinclude-eps-fonts --png --output $(basename $@) $<

intro_png.png : intro_png.ly intro.ly
	 lilypond -dbackend=eps -dno-gs-load-fonts -dinclude-eps-fonts --png --output $(basename $@) $<



all: $(project).pdf

delivery : $(project).pdf
	cp  $(project).pdf $(DESTDIR)/.