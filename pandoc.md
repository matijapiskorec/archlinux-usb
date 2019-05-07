# Document conversion and generation with pandoc

Install pandoc:
```
sudo pacman -Syu pandoc
```

Convert markdown to pdf with pdflatex:
```
pandoc [INPUT MARKDOWN] --pdf-engine=pdflatex -o [OUTPUT PDF]
```

Pandoc can read from standard input, so you can pipe markdown to it. For example, if you want to pipe a markdown file starting from line 12 and generate a pdf with table of contents and numbered sections:
```
tail +12 [PATH TO THIS MARKDOWN] | pandoc --pdf-engine=pdflatex -o [PATH TO PDF OUTPUT] --toc --number-sections
```

If you want to add some metadata to your markdown, you can specify it at the beginning of a markdown file and it will be rendered properly based on the output type:
```
% Title
% Author
% Date
```