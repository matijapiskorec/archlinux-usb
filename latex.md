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

## Font Awesome in XeLaTeX

If you want to use Font Awesome glyphs, for example `\faPlus` and `\faEnvelope`, in your XeLaTeX files you have to include fontspec and fontawesome packages:
```
% Needed for \faPlus and \faEnvelope font gylphs when using XeLaTeX
\usepackage{fontspec}
\usepackage{fontawesome}
```

Overview of all other Font Awesome glyphs:
<https://ctan.ijs.si/tex-archive/fonts/fontawesome/doc/fontawesome.pdf>

## Code with syntax highlighting in LaTeX

If you want to include code with syntax highlighting in your LaTeX code you can use package minted which is included in Pacman. You also need python-pygments which minted uses:
```
sudo pacman -Syu python-pygments minted
```

Now you can include minted in your .tex file:
```
\usepackage{minted}
```

Make sure you are compiling with `--shell-escape` option, for example with XeLaTeX:
```
xelatex -interaction nonstopmode --shell-escape main
```

If you are including code in your Beamer project make sure you are adding `[fragile]` option to your slides as otherwise minted environment will break your Beamer slides (this happens with all verbatim environments). A full working example is here (along with some options for better formating):
```
\begin{frame}[fragile]
\frametitle{Code example in Beamer}

\begin{minted}
[
framesep=2mm,
baselinestretch=1.2,
fontsize=\footnotesize,
linenos
]
{python}
import numpy as np
\end{minted}

\end{frame}
```

You can also include inline code with `\mint` command, for example HTML:
```
\mint{html}|<h2>Something <b>here</b></h2>|
```

For more examples see Overleaf page:
<https://www.overleaf.com/learn/latex/Code_Highlighting_with_minted>

## Latexdiff

Using Latexdiff for marking changes to Tex documents:
<https://www.overleaf.com/learn/latex/Articles/Using_Latexdiff_For_Marking_Changes_To_Tex_Documents>

Suggestion from Alberto Partida how to use latexdiff to highlight changes between two papers in LaTeX (there is an option to include abstract as well otherwise it's excluded):
```
latexdiff --append-context2cmd="abstract" -e utf8 oldfile.tex newfile.tex > diff-abs-final.tex
```

You can also use latediff with combination with git or some other versioning system to manage multiple revisions! For that you can use a wrapper script `latexdiff-vc`. For example, to compare two git revisions rev1 and rev2:
```
latexdiff-vc -r rev1 -r rev2 file.text
```

## Normal text size in Beamer slides

To set the font size of the normal text in Beamer, just put this in the document header:
```
% Set font size of normal text!
\setbeamerfont{normal text}{size=\small}
\AtBeginDocument{\usebeamerfont{normal text}}
```

This is an easy way to increase the amount of text you can fit on a single slide!

