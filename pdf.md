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

Install wkhtmltopdf to convert html webpages to pdf:
```
git clone https://aur.archlinux.org/wkhtmltopdf-static.git
cd wkhtmltopdf-static
makepkg -sri
```

Convert html webpage to pdf:
```
wkhtmltopdf [URL] [FILE NAME].pdf
```

Extract pages 1, 2, and 3 to 5 using pdfjam:
```
pdfjam file1.pdf 1,2,3-5 -o file2.pdf
```

## Extraction of text from pdf

You can extract text from pdf using pdftotext, which is a part of poppler package:
```
sudo pacman -Syu poppler
```

Now you can extract text from pdf:
```
pdftotext [PDF FILE] [TXT FILE]
```

Unfortunatelly, Adobe pdf comments (in form of popup annotations or sticky notes) will not be extracted! :-(

## Searching within pdf file

To search a text within pdf file you can use pdfgrep:
```
sudo pacman -Syu pdfgrep
```

Now you can search for a keyword within pdf:
```
pdfgrep -nHm 10 "keyword" [PATH TO PDF]
```

