# Manage multiple monitors with xrandr

Install `xorg-xrandr` package for managing displays:
```
sudo pacman -Syu xorg-xrandr
```

Check status of currently available displays:
```
xrandr
```

Switch monitor `DVI-I-2` to be left of `DVI-I-1`:
```
xrandr --output DVI-I-2 --left-of DVI-I-1
```

Connect to the external VGA display:
```
xrandr --output VGA1 --auto
```

Disconnect from the external VGA display:
```
xrandr --output VGA1 --off
```
