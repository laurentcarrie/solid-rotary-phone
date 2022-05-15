project=amy-winehouse-you-know-i-m-no-good
include $(CURDIR)/../../../macros/Makefile


$(project).pdf : song.tex lyrics.tex grille.tex build/break_png.png
	bash $(buildtex) $(project)


build/break_png.png : break_png.ly break.ly
	bash $(buildpngly) $^


break_midi.midi : break_midi.ly break.ly
	lilypond -dmidi-extension=midi --output break_midi break_midi.ly

all : break_midi.midi $(project.pdf)