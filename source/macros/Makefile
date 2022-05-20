.PHONY: clean pdf delivery-song

buildtex=$(CURDIR)/../../../macros/buildtex.sh
buildpngly=$(CURDIR)/../../../macros/buildpngly.sh

pdf: $(project).pdf

all: $(project).pdf

delivery-song : $(DESTDIR)/$(project).pdf


$(DESTDIR)/$(project).pdf : $(project).pdf
	echo "ZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZ $(project)"
	mkdir -p $(DESTDIR)
	cp  $(project).pdf $(DESTDIR)/.

clean :
	rm -rf build
	rm -rf *.pdfF