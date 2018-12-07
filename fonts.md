# Install and setup fonts

Install couple of fonts:
```
sudo pacman -Syu terminus-font
sudo pacman -Syu ttf-hack
sudo pacman -Syu adobe-source-code-pro-fonts
sudo pacman -Syu inconsolata
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