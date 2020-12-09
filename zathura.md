# Zathura document viewer

Install Zathura and optional dependencies:
```
sudo pacman -S zathura
sudo pacman -S --asdeps zathura-djvu zathura-pdf-mupdf zathura-ps
```

Run a pdf document with:
```
zathura [document.pdf]
```

Commands:
Adjust window in best fit or width mode: `a`, `s`
Zoom in and out: `+`, `-`
Search: `/`, `?`
Search next/previous result: `n`, `N`
Rotate 90 degrees: `r`
Recolor (invert colors): `Ctrl r`
Reload document: `R`
Toggle dual page mode: `d`
Switch to fullscreen mode: `F11`
Swith to presentation mode: `F5`
Toggle status bar: `Ctrl n`
Quit: `q`

Commands in the command mode:
Save file: `:write [PATH]`
Close document: `:close`

## Read from stdin

Zathura can read from stdin. For example, you can convert a markdown file on the fly and output it to Zathura:
```
cat README.md | pandoc --pdf-engine=pdflatex --from markdown --to pdf | zathura -
```

