MAKEFILES=$(shell find . -maxdepth 3 -type f -name Makefile)
SUBDIRS=$(filter-out ./,$(dir $(MAKEFILES)))

.PHONY: all clean
.DEFAULT: all

SHELL=/bin/bash


all:
	echo $(SUBDIRS)
	for dir in $(SUBDIRS); do \
    	echo $$dir ; \
        make -C $$dir all; \
    done

clean:
	echo $(SUBDIRS)
	for dir in $(SUBDIRS); do \
    	echo $$dir ; \
        make -C $$dir clean ; \
    done
