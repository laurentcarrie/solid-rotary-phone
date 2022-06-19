.PHONY: clean pdf delivery-song

buildtex=$(CURDIR)/../macros/buildtex.sh
buildbook=$(CURDIR)/../../cxx/solid_rotary_phone_make_book



%.pdf : %.tex
	rm -rf tmpbuild-$<
	echo $<
	$(buildbook) $< tmpbuild-$<
	mv tmpbuild-$</$< tmpbuild-$</song.tex
	( cd tmpbuild-$< && bash $(buildtex) song.tex *.tex *.ly )
	cp tmpbuild-$</song.pdf $@
	rm -rf tmpbuild-$<



delivery : sunny-bd.pdf move-the-line.pdf
	mkdir -p ../../delivery/books ; \
   for name in *.pdf ; do \
        cp $${name} ../../delivery/books/. ; \
    done


move-the-line : move-the-line.pdf

sunny-bd : sunny-bd.pdf

clean :
	rm -f *.pdf
	rm -rf tmpbuild-*