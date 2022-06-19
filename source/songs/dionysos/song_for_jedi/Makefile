project=dionsysos-song-for-jedi

include $(CURDIR)/../../../macros/Makefile

sources=song.tex lyrics.tex grille.tex body.tex

$(project).pdf : $(sources)
	bash $(buildtex) $@ $^

pdf : $(project.pdf)

clean :
	rm -rf build
	rm -rf *.pdf

song-for-jedi : $(sources)
	rm -rf build *.pdf
	bash $(buildtex) $@ $^
