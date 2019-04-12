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
