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
