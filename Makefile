# Minimal makefile for Sphinx documentation
#

# You can set these variables from the command line, and also
# from the environment for the first two.
SPHINXOPTS    ?=
SPHINXBUILD   ?= sphinx-build
SOURCEDIR     = source
BUILDDIR      = build



# Put it first so that "make" without argument is like "make help".
help:
	@$(SPHINXBUILD) -M help "$(SOURCEDIR)" "$(BUILDDIR)" $(SPHINXOPTS) $(O)

.PHONY: help Makefile  pdf html s3 clean wav

# Catch-all target: route all unknown targets to Sphinx using the new
# "make mode" option.  $(O) is meant as a shortcut for $(SPHINXOPTS).
#%: Makefile $(lilypond_png)
#	$(SPHINXBUILD) -M $@ "$(SOURCEDIR)" "$(BUILDDIR)" $(SPHINXOPTS) $(O)

start :

%.png : %.ly
	ly reformat -o $< $<
	lilypond -dbackend=eps -dresolution=600 --png --output $(@:.png=) $<

%.midi : %.ly
	lilypond -dmidi-extension=mid $<

%.wav : %.midi
	fluidsynth -F $@ /usr/share/sounds/sf2/FluidR3_GM.sf2 $<

src_files= \
	conf.py \
	index.rst \
	bohemian-like-you.rst \
	scar-tissue.rst \
	creep.rst


lilypond_png= \
	$(SOURCEDIR)/bohemian-like-you.png \
	$(SOURCEDIR)/bohemian-like-you-voice.png \
	$(SOURCEDIR)/scar-tissue.png

lilypond_wav= \
	$(SOURCEDIR)/bohemian-like-you.wav \
	$(SOURCEDIR)/bohemian-like-you-voice.wav \
	$(SOURCEDIR)/scar-tissue.wav

images : $(lilypond_png)


wav : $(lilypond_wav)
	mkdir -p $(BUILDDIR)/html/wav
	cp $(SOURCEDIR)/*.wav $(BUILDDIR)/html/wav/.

html :  images wav
	$(SPHINXBUILD) -M html "$(SOURCEDIR)" "$(BUILDDIR)" $(SPHINXOPTS) $(O)

pdf :  images wav
	@$(SPHINXBUILD) -M latexpdf "$(SOURCEDIR)" "$(BUILDDIR)" $(SPHINXOPTS) $(O)


s3 : html pdf wav
	aws s3 cp --recursive build/html/ s3://s3-lolo-web/labandeapierrestephanecelinelaurent/html
	#aws s3 cp  build/latex/labandepierrestphaneclinelaurent.pdf s3://s3-lolo-web/pdf/labandepierrestphaneclinelaurent.pdf

clean :
	rm -f $(SOURCEDIR)/*.wav
	rm -f $(SOURCEDIR)/*.tex
	rm -f $(SOURCEDIR)/*.texi
	rm -f $(SOURCEDIR)/*.count
	rm -f $(SOURCEDIR)/*.png
	rm -f $(SOURCEDIR)/*.pdf
	rm -f $(SOURCEDIR)/*.eps
	rm -f $(SOURCEDIR)/snippet*.ly
