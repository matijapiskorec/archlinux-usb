# Feh image viewer

Install `feh` image viewer and background setter:
```
sudo pacman -Syu feh
```

Set background:
```
feh --bg-fill image.jpg
```

View images from a folder:
```
feh --scale-down --auto-zoom Images/
```

If you want that these arguments become defaults put alias in your `~/.bashrc`:
```
alias feh='feh --scale-down --auto-zoom'
```

You can also put it in rifle configuration so that it runs by default in ranger. Put the following line in `~/.config/ranger/rifle.conf`:
```
mime ^image, has feh, X, flag f = feh --scale-down --auto-zoom -- "$@"
```