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

Extracting page 2 using pdftk:
```
pdftk main.pdf cat 2 output output.pdf
```

Extracting multiple pages using pdftk:
```
pdftk main.pdf cat 1 3 5-6 output output.pdf
```

Combining the two single-page PDF's into a single-page PDF, where pages are on top of eachother on a single page:
```
pdfjam output1.pdf output2.pdf --nup 1x2 --outfile output3.pdf
```

Consider using an `--landscape` option if you need to orient the pages differently, together with the `--nup` option.

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

Extract text from multiple pdf's using xargs:
```
find ~/path/ -type f -name "*.pdf" -print0 | xargs -0 -I {} pdftotext "{}" - 2>/dev/null
```

For searching the stream you can pipe the output to grep or ag along with the keyword `grep "keyword"` or `ag "keyword"`. This will not give you filenames though, for this you probably need a more powerful script.

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

Zathura and MuPDF cannot fill in PDF forms. Foxit Reader can but sometimes there is a problem with it. So I decided to install Acrobat Reader from AUR:
```
git clone https://aur.archlinux.org/acroread.git
cd acroread
makepkg -sri
```

Unfortunatelly, it crashes often while filling in the form:-( I tried installing Adobe Reader for Wine but installation could not complete. So I tried Evince reader from the official repository:
```
sudo pacman -Syu evince
```

And this one works fine! So I will be using Foxit Reader and Evince for filling in the PDF forms.

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

## Converting PDF to an image

You can convert a PDF to an image (in this case it makes sense if PDF is one-page):
```
convert file.pdf -density 300 -depth 8 -quality 85 -colorspace RGB file.png
```

## Combining separate PDF's

To combine all PDF's in the current folder, assuming you are using fish interactive shell:
```
pdftk (ls -1 -cr *.pdf) cat output combined.pdf
```

In general you can combine multiple PDF's in the following way:
```
pdftk file1.pdf file2.pdf cat output combined-file.pdf
```

## Inster an image into PDF

Unfortunatelly, I could not find any offline tools for inserting a simple image into PDF (for example, for a signuture). But I found this online tool which works ok:
<https://smallpdf.com/edit-pdf>

For a simple one-page PDF you can use Inkscape. Import PDF and any image you need, then export back to PDF. I have to figure out how to export multipage documents properly!


