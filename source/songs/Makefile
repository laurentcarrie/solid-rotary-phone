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
    rm -rf $(DESTDIR) ;\
	for dir in $(SUBDIRS); do \
    	echo $$dir ; \
        make -C $$dir clean ; \
    done

delivery:
	echo $(SUBDIRS) ;\
    rm -rf $(DESTDIR) ;\
    mkdir $(DESTDIR) ; \
	for dir in $(SUBDIRS); do \
    	echo $$dir ; \
        make -C $$dir delivery DESTDIR="$(DESTDIR)" ; \
    done
