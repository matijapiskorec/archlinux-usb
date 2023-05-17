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

You can also specify these as YAML metadata:
```
---
Title: Full Title
Author: Author One
Date: date
...
```

## References

If you want to manage references and cross-references, install pandoc-citeproc and pandoc-crossref:
```
sudo pacman -Syu pandoc-citeproc pandoc-crossref
```

Cross-references are used in a following way:
```
$$ math $$ {#eq:label}
[-@eq:label]
```

You have to use `eq` for equations and `sec` for sections! Minus `-` in front of a reference is to suppress default prefix like `fig.` and `sec.` in the output text.

Cross-references are compiled with:
```
pandoc [INPUT MARKDOWN] --filter pandoc-crossref -o [OUTPUT PDF]
```

Bibliographic references are used in a following way:
```
[@AuthorYear]
```

Where `AuthorYear` is a label from `.bib` file:
```
@book{AuthorYear,
	doi = {doi},
	author = {author},
	title = {title}
}
```

To compile your markdown with references just add `--bibliography=file.bib --citeproc` option when you compile with pandoc. In this simple case you do not have to add `--filter pandoc-citeproc`. Bibliographic references will be added at the end of the output pdf in Chichago citation style. Note from January 2021 - for some reason the `--filter pandoc-citeproc` does not work anymore (I have to test this more), it seems like it was replaced with simply `--citeproc`.

## Links 

To have hyperlinked and colored links put the following in your YAML metadata declaration: 
```
link-citations: true
colorlinks: true
```

## Output to standard output

You can use pandoc to output to standard output, and then read from some other program that reads from standard input on the fly. For example, generate a pdf from markdown and load it directly in Zathura:
```
cat README.md | pandoc --pdf-engine=pdflatex --from markdown --to pdf | zathura -
```

## Math in epub

Math works fine for LaTeX/PDF output. However, if you want math output in epub format you have to make sure you are outputing in epub3 which uses MathML to display formulas, and not epub2 which is default:
```
pandoc input.md -t epub3 --toc --number-sections --filter pandoc-crossref --bibliography=bibliography.bib -o output.epub
``` 

Zathura is not capable of properly displaying MathML formulas in epub3. For proper display you can use Calibre.
 
## Change default font in Markdown

Pandoc uses LaTeX by default for PDF document generation, so in order to change the default font for the whole document you can include this command in the header:
```
fontfamily: opensans
header-includes:
  - \renewcommand{\familydefault}{\sfdefault}
```

## Structuring the slide show

You can structure your Beamer Pandoc presentation by using `--slide-level 2` option while compiling and including sections and subsections within your markdown:
<https://pandoc.org/MANUAL.html#structuring-the-slide-show>

A heading at the slide level always starts a new slide.

Headings below the slide level in the hierarchy create headings within a slide. (In beamer, a "block" will be created. If the heading has the class example, an exampleblock environment will be used; if it has the class alert, an alertblock will be used; otherwise a regular block will be used.)

Headings above the slide level in the hierarchy create "title slides," which just contain the section title and help to break the slide show into sections.

So the Markdown structure might look like this for `--slide-level 2`:
```
# This is a section slide

## This is the first slide in this section
 - list item 1
 - list item 2

## This is the second slide in this section

### This creates a heading within a slide - a block in case of Beamer
```

## Tutorials for Pandoc

Customizing pandoc to generate beautiful pdf and epub from markdown
<https://learnbyexample.github.io/customizing-pandoc/>

