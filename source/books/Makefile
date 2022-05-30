.PHONY: clean pdf delivery-song

buildtex=$(CURDIR)/../macros/buildtex.sh
buildbook=$(CURDIR)/../../cxx/solid_rotary_phone_make_book



sunny-bd.pdf :
	rm -rf tmpbuild
	$(buildbook) sunny-bd.tex tmpbuild
	mv tmpbuild/sunny-bd.tex tmpbuild/song.tex
	( cd tmpbuild && bash $(buildtex) song.tex *.tex *.ly )
	cp tmpbuild/song.pdf $@
	rm -rf tmpbuild

delivery : sunny-bd.pdf
	mkdir -p ../../delivery/books
	cp sunny-bd.pdf ../../delivery/books/.