# i3 tilling window manager

To start i3 as soon as X starts add following line to `~/.xinitrc`:
```
exec i3
```

Then you can start X manually from tty by running:
```
startx
```

Our you can do it at startup by adding following line to `~/.bash_profile`, preferably near the end:
```
[ "$(tty)" = "/dev/tty1" ] && ! pgrep -x i3 >/dev/null && exec startx
```

Your tty1 virtual console will now be running i3. If you want to log out from a virtual console press `Ctrl+Alt+BackSpace`. You can also change a virtual console by pressing `Ctrl+Alt+F1` through `Ctrl+Alt+F2`. 

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

Add following configuration for rxvt in your `~/.Xresources` file to manage transparency:
```
urxvt*depth: 32
urxvt*background: rgba:0000/0000/0200/c800
```

Also, add these lines to `~/.Xresources` to make rxvt dark and pretty:
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
