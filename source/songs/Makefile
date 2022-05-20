MAKEFILES=$(shell find . -maxdepth 3 -type f -name Makefile)
SUBDIRS=$(filter-out ./,$(dir $(MAKEFILES)))
ROOT_DIR:=$(shell dirname $(realpath $(firstword $(MAKEFILE_LIST))))
DESTDIR:=$(ROOT_DIR)/../../delivery


.PHONY: all clean delivery delivery-books delivery-songs
.DEFAULT: all

SHELL=/bin/bash


all:
	echo $(SUBDIRS)
	for dir in $(SUBDIRS); do \
    	echo $$dir ; \
        make -C $$dir all; \
    done

clean:
	echo $(SUBDIRS) ;\
    rm -rf $(DESTDIR) ;\
	for dir in $(SUBDIRS); do \
    	echo $$dir ; \
        rm -rf $$dir/build ;\
        rm -rf $$dir/*.pdf ;\
    done ; \
    rm -rf build

delivery-song: pdf
	echo "YYYYYYYYYYYYYYYYYYYYYYYYY" ; \
	echo $(SUBDIRS) ;\
    rm -rf $(DESTDIR)/songs ;\
    mkdir -p $(DESTDIR)/songs ; \
	for dir in $(SUBDIRS); do \
    	echo $$dir ; \
        make -C $$dir delivery-song DESTDIR="$(DESTDIR)/songs" ; \
    done ;

books=sunny-bd.pdf ultimate-chorus.pdf spcl.pdf

delivery-books: $(books)
	mkdir -p $(DESTDIR)/books/ ; \
	for b in $(books) ; do \
    	cp $$b $(DESTDIR)/books/. ; \
    done ;

delivery : delivery-songs delivery-books

pdf:
	echo $(SUBDIRS) ;\
	for dir in $(SUBDIRS); do \
    	echo $$dir ; \
        make -C $$dir pdf ; \
    done


sunny-bd.pdf : sunny-bd.tex pdf
	bash ../macros/buildbook.sh  sunny-bd.tex

spcl.pdf : spcl.tex pdf
	bash ../macros/buildbook.sh  spcl.tex

ultimate-chorus.pdf : ultimate-chorus.tex pdf
	bash ../macros/buildbook.sh  ultimate-chorus.tex
