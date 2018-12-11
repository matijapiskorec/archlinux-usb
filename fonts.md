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