# vifm file manager

Install vifm terminal file manager:
```
sudo pacman -Syu vifm
```

## Setting up a vifm rice from Reddit

To rice it up really nicelly you can use the following configuration:
<https://www.reddit.com/r/unixporn/comments/fx32el/oc_managed_to_get_audio_epub_pdf_video_image_and/>

Dependencies:
```
sudo pip3 install ueberzug
sudo pacman -Syu ffmpegthumbnailer poppler imagemagick

cd src/
git clone https://github.com/marianosimone/epub-thumbnailer
cd epub-thumbnailer
sudo python install.py install

cd ../
git clone git clone https://github.com/sdushantha/fontpreview
cd fontpreview
sudo make install 
```

For the fontpreview you will also need xdotool:
```
sudo pacman -S xdotool
```

(You can now preview the fonts installed in your system with `fontpreview`.)

And you also need following scripts:

vifmrun which you will call instead of vifm (I've put it in `~/.scripts/`):
<https://raw.githubusercontent.com/sdushantha/bin/master/utils/vifmrun>

You can also add alias in your fish config (`~/.config/fish/config.fish`):

    alias vifm 'vifmrun'

Your vifmrc (put it in `~/.config/vifm/`)
<https://raw.githubusercontent.com/sdushantha/dotfiles/master/vifm/.config/vifm/vifmrc>

And a custom script (put it in `~/.config/vifm/scripts/`):
<https://raw.githubusercontent.com/sdushantha/dotfiles/master/vifm/.config/vifm/scripts/vifmimg>

For some reason the image previews do not work in st terminal:-(

