Pacman package manager for Arch Linux

Update pacman:
```
sudo pacman -Sy
```

Install a package:
```
sudo pacman -S [package name]
```

Check all explicitly installed packages:
```
sudo pacman -Qe | less
```

Check whether a specific package is installed:
```
pacman -Qi [package name]
```

Find out optional dependencies for a program:
```
sudo pacman -Si [program]
```

Install optional dependencies for the specific program:
```
sudo pacman -S --asdeps [optional dependencies]
```

Update the whole system:
```
sudo pacman -Syu
```

Install packages from a list `pkglist.txt` (produced by running pacman with `-Qe`):
```
sudo pacman -S --needed - < pkglist.txt
```
