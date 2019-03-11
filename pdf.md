# Manage pdf documents in Arch Linux

Join several pdf documents into one with pdfjam. First, install pdfjam which is a part of texlive-core package:
```
sudo pacman -Syu pdfjam
```

Then, join several pdfs into one:
```
pdfjam *.pdf --outfile output.pdf
```

You can also do it with Ghostscript:
```
gs -dNOPAUSE -sDEVICE=pdfwrite -sOUTPUTFILE=out.pdf -dBATCH 1.pdf 2.pdf 3.pdf
```
