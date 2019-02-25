# Pacman package manager for Arch Linux

Update pacman:
```
sudo pacman -Sy
```

Update the whole system:
```
sudo pacman -Syu
```

Install a package:
```
sudo pacman -S [package name]
```

However, it is recommended you update your system along with every package install:
```
sudo pacman -Syu [package name]
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

Install packages from a list `pkglist.txt` (produced by running pacman with `-Qe`):
```
sudo pacman -S --needed - < pkglist.txt
```

Remove a package:
```
sudo pacman -R [program]
```

Remove a package along with all of its dependecies which are not explicitly required by any other installed package:
```
sudo pacman -Rs [program]
```

