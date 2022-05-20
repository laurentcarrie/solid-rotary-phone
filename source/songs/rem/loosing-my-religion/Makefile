project=rem-loosing-my-religion
include $(CURDIR)/../../../macros/Makefile


$(project).pdf : song.tex body.tex lyrics.tex grille.tex break_png.ly break.ly
	bash $(buildtex) $@ $^




all : $(project.pdf)