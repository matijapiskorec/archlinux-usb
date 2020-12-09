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

Pipe the result of pdftotext directly to vim or to Sublime text using vipe command line utility (in that case you need to make sure your EDITOR shell variable is set to Sublime):
```
pdftotext [PDF FILE] - | vim -
pdftotext [PDF FILE] - | vipe
```

Unfortunatelly, Adobe pdf comments (in form of popup annotations or sticky notes) will not be extracted! :-(

## Searching within pdf file

To search a text within pdf file you can use pdfgrep:
```
sudo pacman -Syu pdfgrep
```

Now you can search for a keyword within pdf:
```
pdfgrep -inHm 10 "keyword" [PATH TO PDF]
```

Search recursivelly all PDF's in a folder and pipe the results to fzf:
```
pdfgrep -irnHm 10 "keyword" [PATH TO FOLDER] | fzf
```

## Optical character recognition with tesseract and ocrmypdf

ocrmypdf is a program available in AUR that adds a searchable text layer to pdfs. Install it through AUR:
```
cd ~/src/
git clone https://aur.archlinux.org/ocrmypdf.git
cd ocrmypdf
makepkg -sri
```

Unfortunatelly, in order for these to work you have to install several other AUR packages by following the same procedure (run `makepkg -sri` in the appropriate directory after each one):
```
cd ~/src
git clone https://aur.archlinux.org/python-pikepdf.git
git clone https://aur.archlinux.org/python-pdfminer.six.git
git clone https://aur.archlinux.org/python-ruffus.git
```

In addition you have to download tesseract language data which is available in the official Arch repository:
```
sudo pacman -Syu tesseract-data-eng tesseract-data-hrv
```

You are now ready to ocr some pdfs! Lets first convert an image to pdf using ImageMagick:
```
convert image.jpg converted-image.pdf
```

You can combine multiple images into a single pdf, as well as rotate and resize them if needed (you can also use `-auto-orient` option):
```
convert -rotate 90 -resize 50% image*.jpg converted-image.pdf
```

Make sure your ImageMagick permissions are set up properly for converting pdfs. Modify `/etc/ImageMagick-6/policy.xml` (check the ImageMagick version!) by changing the line:
```
<policy domain="coder" rights="none" pattern="PDF" />
```

And replace `"none"` by `"read|write"`.

You can now ocr your pdf with (with an optional specification of a language):
```
ocrmypdf -l eng converted-image.pdf converted-image-scanned.pdf
```

You can use tesseract as a standalone tool to perform OCR and output text. It works only on images, not pdf's, and can output to stdout:
```
tesseract image.jpeg stdout -l hrv | vim -
```

## PDF readers

There are several pdf readers you can use - `zathura` and `mupdf` which are command line based and `FoxitReader` which is more similar to standard GUI pdf viewers.

## Creating a combined pdf from har archive

Parse all jpeg urls from a har archive and download all images:
```
cat hararchive.har | grep -o '"url": "https://.*\.jpeg"' | sed 's|"url": "||g;s|"||g;s| ||g' | xargs wget
```

Convert all images in folder in order of creation to a combined pdf (in fish shell):
```
pdfjam (ls -1 -cr *.jpeg) -o output.pdf
convert (ls -1 -cr *.jpeg) -compress jpeg -quality 25 output.pdf
```

See more info on how to create pdf from multiple images and how to perform optical character recognition:
<https://askubuntu.com/questions/246647/convert-a-directory-of-jpeg-files-to-a-single-pdf-document>

