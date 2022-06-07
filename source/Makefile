.PHONY: delivery

.SUBDIRS : songs books

clean :
	rm -rf delivery

delivery:
	echo $(SUBDIRS) ;\
    rm -rf $(DESTDIR)/songs ;\
    mkdir -p $(DESTDIR)/songs ; \
	for dir in $(SUBDIRS); do \
    	echo $$dir ; \
        make -C $$dir delivery DESTDIR="$(DESTDIR)/songs" ; \
    done ; \
	\
    rm -rf $(DESTDIR)/books ;\
    mkdir -p $(DESTDIR)/books ; \
    make -C $$dir delivery DESTDIR="$(DESTDIR)/books" ; \
