project=amy-winehouse-you-know-i-m-no-good
include $(CURDIR)/../../../macros/Makefile


$(project).pdf : song.tex body.tex lyrics.tex grille.tex build/break_png.png
	bash $(buildtex) $@ $^


build/break_png.png : break_png.ly break.ly
	bash $(buildpngly) $^


all : break_midi.midi $(project.pdf)