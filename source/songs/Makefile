MAKEFILES=$(shell find . -maxdepth 3 -type f -name Makefile)
SUBDIRS=$(filter-out ./,$(dir $(MAKEFILES)))
ROOT_DIR:=$(shell dirname $(realpath $(firstword $(MAKEFILE_LIST))))
DESTDIR:=$(ROOT_DIR)/../../delivery


.PHONY: all clean delivery
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
    rm -rf $(DESTDIR)/songs ;\
	for dir in $(SUBDIRS); do \
    	echo $$dir ; \
        rm -rf $$dir/build ;\
        rm -rf $$dir/*.pdf ;\
    done ; \
    rm -rf build

delivery:
	echo "YYYYYYYYYYYYYYYYYYYYYYYYY" ; \
	echo $(SUBDIRS) ;\
    rm -rf $(DESTDIR)/songs ;\
    mkdir -p $(DESTDIR)/songs ; \
	for dir in $(SUBDIRS); do \
    	echo $$dir ; \
        make -C $$dir pdf DESTDIR="$(DESTDIR)/songs" ; \
        cp $$dir/*.pdf $(DESTDIR)/songs/. ; \
    done ;

books=sunny-bd.pdf ultimate-chorus.pdf spcl.pdf

pdf:
	echo $(SUBDIRS) ;\
	for dir in $(SUBDIRS); do \
    	echo $$dir ; \
        make -C $$dir pdf ; \
    done

