# Keyboard layout on Arch Linux

Change keyboard layout in tty:
```
loadkeys croat
```

Make it permanent for tty (saves to `/etc/vconsole.conf`):
```
localectl set-keymap croat
```

To set keymap in X environment run (for permanent change put it in `~/.xinitrc` if you use it):
```
setxkbmap hr
```

This should make configration persistent in X environment but it does not:
```
localectl list-x11-keymap-layouts
localectl set-keymap --no-convert hr
```

To set locale, uncomment `en_US.UTF-8 UTF-8` in `/etc/locale.gen`:
```
sudo nano /etc/locale.gen
```

And then generate locale:
```
locale-gen
```

For manual setup of keymap and console font edit (with sudo) `/etc/vconsole.conf`  with:
```
KEYMAP=croat
FONT=lat9w-16
```

## Keyboard repeat

Adjust typematic delay (amount of time a key needs to be pressed in order for the repeating process to begin) and rate:
```
sudo kbdrate -d 200 -r 30
```

## Swap escape and caps lock key

Swap escape and caps lock key:
```
setxkbmap -option caps:swapescape
```

## klavaro keyboard tutor

You can install and use klavaro keyboard trainer/tutor GUI:
```
sudo pacman -Syu klavaro
```

