.PHONY:  all clean delivery
.DEFAULT=delivery
project=amy-winehouse-you-know-i-m-no-good

include $(CURDIR)/../../../macros/Makefile




$(project).pdf : song.tex lyrics.tex grille.tex break_png.png
	bash $(buildtex) song.tex
	mv song.pdf $(project).pdf

break_png.png : break_png.ly break.ly
	 lilypond -dbackend=eps -dno-gs-load-fonts -dinclude-eps-fonts --png --output $(basename $@) $<


break_midi.midi : break_midi.ly break.ly
	lilypond -dmidi-extension=midi --output break_midi break_midi.ly

all : break_midi.midi $(project.pdf)