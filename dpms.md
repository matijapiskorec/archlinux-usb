# Disabling Display Power Management System (DPMS)

Install `xorg-xset` to be able to control display power management:
```
sudo pacman -S xorg-xset
```

Check current settings with
```
xset q
```

Disable display power management so that display will always stay on (if you want to make it permanent on startup put it into `.xinitrc`):
```
xset -dpms
```