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

Check all explicitly installed packages (add `-q` to list only package names):
```
sudo pacman -Qe | less
```

Check whether a specific package is installed:
```
pacman -Qi [package name]
```

Check which packages need to be updated (in order to get the newest state it's best to first update the package database with `sudo pacman -Sy`):
```
pacman -Qu
```

Find out optional dependencies for a program:
```
sudo pacman -Si [program]
```

Install optional dependencies for the specific program:
```
sudo pacman -S --asdeps [optional dependencies]
```

List orphaned packages, dependencies that are not needed by any other package anymore:
```
pacman -Qdt
```

Install packages from a list `pkglist.txt` (produced by running pacman with `-Qe`):
```
sudo pacman -S --needed - < pkglist.txt
```

Remove a package:
```
sudo pacman -R [program]
```

Remove a package along with all of its dependecies which are not explicitly required by any other installed package (`-s`), and system config files (`-n`):
```
sudo pacman -Rns [program]
```

Clean package cache (old packages which are not needed anymore):
```
sudo pacman -Sc
```

Include a multilib repository which contains 32-bit packages. Uncomment the following lines in the pacman config file `/etc/pacman.conf`:
```
[multilib]
Include = /etc/pacman.d/mirorlist
```

You will need to run `sudo pacman -S` to synchronize package cache in order to make the new packages visible.
