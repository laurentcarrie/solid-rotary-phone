.PHONY:  all clean
.DEFAULT: all
project=muse-feeling-good

texfiles=

clean:
	rm -rf *.wav *.png *.pdf *.aux *.log *.eps *.count *-systems.*



$(project).pdf : song.tex lyrics.tex grille.tex solo_png.png
	pdflatex song.tex
	mv song.pdf $(project).pdf
	rm -rf *.wav *.png *.aux *.log *.eps *.count *-systems.*

solo_png.png : solo_png.ly solo.ly
	 lilypond -dbackend=eps -dno-gs-load-fonts -dinclude-eps-fonts --png --output $(basename $@) $<



all: $(project).pdf