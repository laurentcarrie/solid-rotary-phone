# Minimal makefile for Sphinx documentation
#

# You can set these variables from the command line, and also
# from the environment for the first two.
SPHINXOPTS    ?=
SPHINXBUILD   ?= sphinx-build
SOURCEDIR     = source2
BUILDDIR      = build

# Put it first so that "make" without argument is like "make help".
help:
	@$(SPHINXBUILD) -M help "$(SOURCEDIR)" "$(BUILDDIR)" $(SPHINXOPTS) $(O)

.PHONY: help Makefile  pdf html s3 mount

# Catch-all target: route all unknown targets to Sphinx using the new
# "make mode" option.  $(O) is meant as a shortcut for $(SPHINXOPTS).
#%: Makefile $(lilypond_png)
#	$(SPHINXBUILD) -M $@ "$(SOURCEDIR)" "$(BUILDDIR)" $(SPHINXOPTS) $(O)

start :

%.png : %.ly
	lilypond -dbackend=eps -dresolution=600 --png --output $(@:.png=) $<

src_files= \
	conf.py \
	index.rst \
	bohemian-like-you.rst \
	scar-tissue.rst \
	cree.rst


mount :
	rm -rf $(SOURCEDIR)
	cp -R source $(SOURCEDIR)


lilypond_png= \
	$(SOURCEDIR)/bohemian-like-you.png \
	$(SOURCEDIR)/scar-tissue.png

images : $(lilypond_png)

html :  mount images
	$(SPHINXBUILD) -M html "$(SOURCEDIR)" "$(BUILDDIR)" $(SPHINXOPTS) $(O)

pdf :  mount images
	@$(SPHINXBUILD) -M latexpdf "$(SOURCEDIR)" "$(BUILDDIR)" $(SPHINXOPTS) $(O)

s3 : html pdf
	aws s3 cp --recursive build/html/ s3://s3-lolo-web/html
	aws s3 cp  build/latex/labandepierrestphaneclinelaurent.pdf s3://s3-lolo-web/pdf/labandepierrestphaneclinelaurent.pdf
