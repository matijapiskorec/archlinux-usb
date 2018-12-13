# Disabling Display Power Management System (DPMS)

Install `xorg-xset` to be able to control display power management:
```
sudo pacman -S xorg-xset
```

Check current settings with
```
xset q
```

Disable display power management and prevent screen from blanking (monitor is turned on but with a black image):
```
xset s off -dpms
```

If you want to make it permanent on startup put it into `.xinitrc`.
