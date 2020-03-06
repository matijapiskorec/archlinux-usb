# LaTeX installation on Arch Linux

Install Tex Live package bundle:
```
sudo pacman -S texlive-most
```

To see all package categories in `texlive-most` check [here](https://www.archlinux.org/groups/x86_64/texlive-most/):
```
texlive-bibtexextra
texlive-core
texlive-fontsextra
texlive-formatsextra
texlive-games
texlive-humanities2018-09-05 	
texlive-latexextra
texlive-music
texlive-pictures
texlive-pstricks
texlive-publishers
texlive-science
```

Tex Live is the same distribution used in [Overleaf](https://www.overleaf.com/), so after installing this you should be able to compile projects downloaded from there.

Download a project with input and output files, then unzip them in the target directory:
```
mkdir /target/directory
unzip /path/to/archive.zip -d /target/directory
```

Now you can compile `main.tex` to `main.pdf` with:
```
pdflatex main
```

Updating bibliography needs extra compilation:
```
bibtex main
```

## Autocompilation with make

We can use make program for automatic compilation of our Latex document. We specify dependencies between different files of the project in the Makefile (which file is needed for compilation of which other) so that make knows how to reproduce the project. Following Makefile is reproduced from [here](https://gist.github.com/yy/808914):
```
TEX = pdflatex -interaction nonstopmode
BIB = bibtex

PAPER = test
BIBFILE = test.bib
FIGURES = figures/

$(PAPER).pdf: $(PAPER).tex $(PAPER).bbl $(FIGURES)* 
	$(TEX) $(PAPER) 
	$(TEX) $(PAPER)

$(PAPER).bbl: $(PAPER).tex $(BIBFILE)
	$(TEX) $(PAPER)
	$(BIB) $(PAPER)

clean::
	rm -fv *.aux *.log *.bbl *.blg *.toc *.out *.lot *.lof $(PAPER).pdf

```

Makefile needs to be in the root of our project, then we can compile our Latex project with:
```
make
```

This will by default run the first target in Makefile, which in our case is `test.pdf`, producing the desired Latex document. Subsequent running of make will have no effect if none of the files changed. This includes figures in figures folder which we track with `$(FIGURES)*`. Running `make clean` target removes all of the generated files currently in the project.

We can automatically rerun make command whenever any of the files changes with the entr program. First, install entr:
```
sudo pacman -Syu entr
```

Then run entr in the project folder:
```
ls *.tex *.bib figures/* | entr make
```

This will track all existing tex and bib files, as well figures in figures folder, and rerun make when any of them changes. If you are using zathura as a pdf viewer, your output pdf will automatically update as well. Unfortunatelly, deleting some of the existing files will crash entr, and adding new files will have no effect because entr does not tracks them.

In theory, make can be used to reproduce the whole data scientific workflow. More  information on how to use it in reproducible scientific research is available [here](http://kbroman.org/minimal_make/).

## Some useful Latex commands

While compiling a Latex code there can be errors due to which compiler halts and seeks input. In these cases you typically want to abort compilation and start again. To abort compilation simply type `X` into the command line and press enter.


