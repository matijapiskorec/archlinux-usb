# Terminal recording with ttyrec

Install enchanced version of ttyrec from AUR:
```
git clone https://aur.archlinux.org/ovh-ttyrec-git.git
cd ovh-ttyrec-git
makepkg -sri
```

Now you can record your terminal session with:
```
ttyrec -f test.rec
```

And replay it with:
```
ttyplay test.rec
```

Install ttygif to convert recordings to gif files:
```
git clone https://aur.archlinux.org/ttygif.git
cd ttygif
makepkg -sri
```

Convert your terminal recording to gif:
```
ttygif test
```

You can view your animated gif using Firefox or Surf browsers:
```
firefox test.gif
surf test.gif
```

As an alternative you can use terminalizer:
<https://github.com/faressoft/terminalizer>

## Rendering images in the terminal with hiptext

This is just for fun, but you can render images and video from terminal using hiptext (available in AUR as well)
<https://github.com/jart/hiptext>

Unfortunatelly, rendering quality is more for fun than anything else:-)

