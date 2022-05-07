buildtex=$(CURDIR)/../../../macros/buildtex.sh

pdf: $(project).pdf

clean:
	rm -rf *.wav *.png *.pdf *.aux *.log *.eps *.count *-systems.*


all: $(project).pdf

delivery : $(project).pdf
	cp  $(project).pdf $(DESTDIR)/.


