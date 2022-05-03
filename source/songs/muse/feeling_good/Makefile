.PHONY:  all clean
.DEFAULT: all
project=muse-feeling-good

texfiles=

clean:
	rm -rf *.wav *.png *.pdf *.aux *.log


$(project).pdf : song.tex lyrics.tex
	pdflatex song.tex
	mv song.pdf $(project).pdf


all: $(project).pdf