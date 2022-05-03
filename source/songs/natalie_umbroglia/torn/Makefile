.PHONY:  all clean deliver
.DEFAULT: all
project=natalie-umbrogila-torn

texfiles=

clean:
	rm -rf *.wav *.png *.pdf *.aux *.log *.eps *.count *-systems.*



$(project).pdf : song.tex lyrics.tex grille.tex
	pdflatex song.tex
	pdflatex song.tex
	mv song.pdf $(project).pdf

solo_png.png : solo_png.ly solo.ly
	 lilypond -dbackend=eps -dno-gs-load-fonts -dinclude-eps-fonts --png --output $(basename $@) $<

intro_png.png : intro_png.ly intro.ly
	 lilypond -dbackend=eps -dno-gs-load-fonts -dinclude-eps-fonts --png --output $(basename $@) $<



all: $(project).pdf

deliver : $(project).pdf
	cp  $(project).pdf $(DESTDIR)/.