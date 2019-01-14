# i3 tilling window manager

Start i3 tilling window manager at boot...

You can start X manually by simply:
```
startx
```

Our you can do it at startup by assing following lines to `~/.bashrc`:
```
if [[ -z $DISPLAY ]] && [[ $(tty) = /dev/tty1 ]]; then
startx
fi
```

To start i3 as soon as X starts add following line to `~/.xinitrc`:
```
echo "exec i3" >> ~/.xinitrc
```

If you want to install Gnome as a desktop environment, which comes fully equiped with  tons of applications (maybe even too much for my taste) you should run:
```
sudo pacman -S [gnome|lxdm]
sudo systemctl start [gdm|lxdm].service
sudo systemctl enable [gdm|lxdm].service
```

There are also options "stop" and "disable" for services.

Install Xorg server, i3 window manager, LightDM display manager, and two terminals 
(rxvt will be used as default, xterm is a fallback option):
```
sudo pacman -S xorg-server xorg-xinit xorg-xclock xorg-twm xterm rxvt-unicode
sudo pacman -S i3 dmenu
sudo pacman -S lightdm lightdm-gtk-greeter
```

Some other xorg packages might be needed:
```
sudo pacman -S xorg-server-xephyr xorg-backlight ttf-dejavu
```

Make sure i3 is started when X starts:
```
sudo 'exec i3' > ~/.xinitrc
```

Start LightDM service (if you want autostart put 'enable' instead of 'start'):
```
systemctl start lightdm.service
```

On the first start i3 should prompt you for the setup. If not, just run:
```
i3-config-wizard
```

It creates i3 config file in `~/.config/i3/config`. Before you rerun the i3-config-wizard make sure to delete the old config.

Setup gaps between windows in i3-gaps (probably installed by default instead of i3-wm) by adding following lines in `~/.config/i3/config` (measurement is in px):
```
gaps inner 5
gaps outer 5
```

To apply changes to i3 config, restart i3 with `$mod-Shift-r`.

Setup desktop background:
```
sudo pacman -S feh
feh --bg-fill geeky_wallpaper.png
```

For startup, put it into `~/.xinitrc`:
```
echo 'feh --bg-fill geeky_wallpaper.png' >> ~/.xinitrc
```

If you have no background image, you can fetch them with wget:
```
sudo pacman -S wget
wget https://www.dropbox.com/s/d8rr7mjb4ifa8u4/geeky_wallpaper.png?dl=0
```

Set transparent terminal windows with Compton:
```
sudo pacman -S compton
```

Run compton as a daemon, without shadow effects (for autostart, put it into `~/.xinitrc`):
```
compton -CGb
```

Add following configuration for rxvt in your `~/.Xdefaults` file to manage transparency:
```
urxvt*depth: 32
urxvt*background: rgba:0000/0000/0200/c800
```

Also, add these lines to `~/.Xdefaults` to make rxvt dark and pretty:
```
URxvt*scrollBar: false
URxvt*background: Black
URxvt*foreground: White
URxvt*colorUL: yellow
URxvt*underlineColor: yellow
URxvt.font: xft:monospace:size=8
```

Restart your xrdb:
```
xrdb .Xresources
```

If you don't need a display manager (LightDM) and want to start X manually you can  simply configure `~/.xinitrc` with something like:
```
setxkbmap hr
feh --bg-fill ~/geeky_wallpaper.png
compton -CGb
xrdb ~/.Xresources
exec i3
```

And then, after logging to tty with your credentials, start X manually with:
```
startx
```

If you later want to kill X server and return to tty simply use `Ctrl-Alt-Backspace` 
shortcut. 

Setup conky:
```
sudo pacman -S conky
conky -bd
```

Setup a color theme matching your chosen background with pywal and 50% terminal transparency:
```
sudo pacman python-pywal python-setuptools
wal -i [PATH-TO-WALLPAPER] -a 50
```

Two themes that I find visually appealing:
```
wal -i Images/1359330091856.jpg -a 95 --saturate 0.8
wal -i Images/1432908749300.jpg -a 95 --saturate 0.8
```

To make a theme persistent on boot add following line to `~/.xinitrc`:
```
wal -R
```

However, this does not work as expected, and so I decided to add `#include` statement in `.Xresources` that loads generated theme colors (located in `.cache/wal/`) directly:
```
#include "Themes/wal-red/colors.Xresources"
```

To list all colors available in `.Xresources`:
```
(x=`tput op` y=`printf %76s`;for i in {0..15};do o=00$i;echo -e ${o:${#o}-3:3} `tput setaf $i;tput setab $i`${y// /=}$x;done)
```

To set the same colors to tty put following in your `.bash_profile`:
```
source ~/Theme/wal-red/colors.Xresources
```

To include cool colored prompt with git information (idea from this [page](https://stackoverflow.com/questions/4133904/ps1-line-with-git-current-branch-and-colors)) add the following to your `.bashrc`:
```
function color_my_prompt {
    local __user_and_host="\[\033[01;32m\]\u\[\033[01;34m\]@\h"
    local __cur_location="\[\033[01;34m\]\w"
    local __git_branch_color="\[\033[31m\]"
    local __git_branch='`git branch 2> /dev/null | grep -e ^* | sed -E  s/^\\\\\*\ \(.+\)$/\(\\\\\1\)\ /`'
    local __prompt_tail="\n\[\033[35m\]>"
    local __last_color="\[\033[00m\]"
    export PS1="$__user_and_host $__cur_location $__git_branch_color$__git_branch$__prompt_tail$__last_color "
}
color_my_prompt
```

## Notifications with dunst

Install dunst, a lightweight replacement for notification daemons:
```
sudo pacman -Syu dunst
```

Initialize dunst (you can put it in `.xinitrc`):
```
dunst &
```

Send notifications:
```
notify-send "Notification text!"
```
