# Install a package from Arch User Repository (AUR)

Clone a package from Github:
```
git clone https://github.com/jaagr/polybar.git
```

Install a package (`-i`) and missing dependencies (`-s`) and remove them at the end (`-r`):
```
cd polybar
makepkg -sri
```

Removing a package with pacman is the same as with regular packages:
```
sudo pacman -R polybar
```

In case of polybar, make sure you also install a jsoncpp dependency:
```
sudo pacman -S jsoncpp
```

List all AUR and other foreign packages that have been explicitly installed:
```
sudo pacman -Qqem
```
