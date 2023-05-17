# Install and setup fonts

Install couple of fonts:
```
sudo pacman -Syu terminus-font
sudo pacman -Syu ttf-hack
sudo pacman -Syu adobe-source-code-pro-fonts
sudo pacman -Syu inconsolata
sudo pacman -Syu ttf-lato
```

Include one of the fonts in `.Xresources` (reset it with `xrdb .Xresources`):
```
URxvt*font: xft:Source Code Pro Medium:size=8 
URxvt*font: xft:Inconsolata:size=9
URxvt*font: xft:Hack:size=8
URxvt*font: xft:Terminus:size=6:antialias=false
```

Include one of the fonts in Sublime text editor:
```
"font_face": "Hack"
```

To improve font rendering, edit `/etc/profile.d/freetype2.sh` and uncomment following line (version 40 is the default minimal mode, you can also check 38 which is for Infinality mode):
```
export FREETYPE_PROPERTIES="truetype:interpreter-version=40"
```

Then enable following presets available in `/etc/fonts/conf.avail/` by creating following symbolic links in `/etc/fonts/conf.d/` (if they aren't already there):
```
sudo ln -s /etc/fonts/conf.avail/10-hinting-slight.conf /etc/fonts/conf.d
sudo ln -s /etc/fonts/conf.avail/10-sub-pixel-rgb.conf /etc/fonts/conf.d
sudo ln -s /etc/fonts/conf.avail/11-lcdfilter-default.conf /etc/fonts/conf.d
```

You can also try these:
```
sudo ln -s /etc/fonts/conf.avail/10-antialias.conf /etc/fonts/conf.d
sudo ln -s /etc/fonts/conf.avail/30-urw-aliases.conf /etc/fonts/conf.d
sudo ln -s /etc/fonts/conf.avail/30-win32-aliases.conf /etc/fonts/conf.d
sudo ln -s /etc/fonts/conf.avail/70-yes-bitmaps.conf /etc/fonts/conf.d
```

It appears that this also eliminates annoying flickering in polybar and i3status bar!?

## Manual installation of fonts in ~/.fonts

To install fonts manually in `~/.fonts` directory just copy them there and run the following command:
```
fc-cache -fv
```

I did it for the Palatino Linotype and TheSans LP OpenType 1.641. which I needed for my official university template.

## Fonts in Xelatex

To properly run my university presentation template I had to use xelatex instead of pdflatex, and the following fonts, one from official Pacman repository and one from AUR:
```
sudo pacman -Syu tex-gyre-fonts

cd ~/src/
git clone https://aur.archlinux.org/tex-gyre-math-fonts.git
cd tex-gyre-math-fonts
makepkg -sri
```

Later I also installed this package from AUR as well but I'm not sure whether it contributed anyhow (the university template compiles without problems).
```
git clone https://aur.archlinux.org/otf-texgyre-pagella-math.git
cd otf-texgyre-pagella-math
makepgk -sri
```

The new version of the university template does not compile due to missing Gyre Pagella font?!

    xdvipdfmx:fatal: Cannot proceed without the font: /usr/share/fonts/mathjax2/HTML-CSS/Gyre-Pagella/woff/GyrePagellaMathJax_Symbols-Regular.woff

But when I list the fonts with `fc-list` I can see the fonts which is supposedly missing?

    /usr/share/fonts/mathjax2/HTML-CSS/Gyre-Pagella/woff/GyrePagellaMathJax_Symbols-Regular.woff: TeX Gyre Pagella Math,Gyre Pagella MathJax Symbols:style=Regular

I tried to update the font cache with `fc-cache -fsv` but to no avail!

Other errors reported:

    Package fontspec Warning: Font "TeX Gyre Pagella Math" does not contain
    (fontspec)                requested Script "Math".

    Package fontspec Warning: OpenType feature 'Style=MathScript' (ssty) not
    (fontspec)                available for font 'TeX Gyre Pagella Math' with
    (fontspec)                script '' and language 'Default'.

However, these warnings are present when I compile the old version of the university template as well, so this is not the main problem!

Another option I could try is to give direct path to font in the `.sty` style template file:

    % Change this
    \setmathfont{TeX Gyre Pagella Math} 

    % Into something like this (not an exact path!)
    \setmathfont[Path=/usr/share/fonts/OTF/]{texgyrepagella-math.otf}

It seems that it is a problem wiht xdvipdfmx and not xelatex - when I try to run xelatex with the `--no-pdf` option the error is not there!

The output of the command `xdvipdfmx -vvv main.xdv`:

    TeX Font: /usr/share/fonts/mathjax2/HTML-CSS/Gyre-Pagella/woff/GyrePagellaMathJax_Symbols-Regular.woff loaded at ID=   71, size=20.66pt (scaled 207.4%)

    </usr/share/fonts/mathjax2/HTML-CSS/Gyre-Pagella/woff/GyrePagellaMathJax_Symbols-Regular.woff@20.66pt
    xdvipdfmx:fatal: Cannot proceed without the font: /usr/share/fonts/mathjax2/HTML-CSS/Gyre-Pagella/woff/GyrePagellaMathJax_Symbols-Regular.woff

So LaTeX sees the font and xdvipdfmx does not!

Try these solutions:

XeLaTeX can find font, but xdvipdfmx can't
<https://tex.stackexchange.com/questions/2028/xelatex-can-find-font-but-xdvipdfmx-cant>

xelatex xdvipdfmx error, cannot proceed with font
<https://tex.stackexchange.com/questions/272671/xelatex-xdvipdfmx-error-cannot-proceed-with-font>

It seems that the problem only appears if there are some specific elements in LaTeX source file? Maybe some of the DVI-related graphics packages? When I try to compile some regular presentation using the provided university .sty file everything compiles fine!

## Font Awesome cheatsheet

Font Awesome cheatsheet to copy/paste into your projects:
<https://fontawesome.com/v5/cheatsheet>

## Listing all available fonts

To quickly list all available fonts on the system:
```
fc-list
```

You can search for the font:
```
fc-list | grep -i awesome
```

## Missing character error

Sometimes an accented character will not be rendered at all because you are using a font that doesn't support it:
```
Missing character: There is no š (U+0161) in font TheSans Plain/OT:language=dflt;mapping=tex-text;!
```

I cannot find a solution to this problem! Even using accents explicitly with `\v{s}` and similar is not working! Maybe it can be solved with font fallbacks like in the suggestion bellow, but I didn't manage to do it.

XeLaTeX: Unicode font fallback for unsupported characters
<https://blog.michael.franzl.name/2014/12/10/xelatex-unicode-font-fallback-unsupported-characters/>

