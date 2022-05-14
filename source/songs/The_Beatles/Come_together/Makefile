.PHONY:  all clean delivery
.DEFAULT=delivery
project=beatles-come-together

include $(CURDIR)/../../../macros/Makefile




$(project).pdf : song.tex lyrics.tex grille.tex solo_final_png.png solo_1_png.png
	bash $(buildtex) song.tex
	mv song.pdf $(project).pdf

solo_final_png.png : solo_final_png.ly solo_final.ly
	 lilypond -dbackend=eps -dno-gs-load-fonts -dinclude-eps-fonts --png --output $(basename $@) $<


solo_final_midi.midi : solo_final_midi.ly solo_final.ly
	lilypond -dmidi-extension=midi --output solo_midi solo_midi.ly

solo_1_png.png : solo_1_png.ly solo_1.ly
	 lilypond -dbackend=eps -dno-gs-load-fonts -dinclude-eps-fonts --png --output $(basename $@) $<


solo_1_midi.midi : solo_1_midi.ly solo_1.ly
	lilypond -dmidi-extension=midi --output solo_1_midi solo_1_midi.ly


all : solo_midi.midi $(project).pdf