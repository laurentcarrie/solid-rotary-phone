.PHONY: clean pdf

buildtex=$(CURDIR)/../../../macros/buildtex.sh
buildpngly=$(CURDIR)/../../../macros/buildpngly.sh

pdf: $(project).pdf

all: $(project).pdf

delivery : $(project).pdf
	cp  $(project).pdf $(DESTDIR)/.

clean :
	rm -rf build
	rm -rf *.pdf