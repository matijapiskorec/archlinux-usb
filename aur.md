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

## Installing suckless software

Install a suckless software, for example `dwm` (dynamic window manager):
```
git clone git://git.suckless.org/dwm
cd dwm
make clean install
```

And then run it with (or put it in `.xinitrc`):
```
exec dwm
```

## Updating an AUR package

To update a package, just position in the appropriate folder, pull the new changes with git and rebuild the package:
```
cd ~/src/exodus
git pull
makepkg -sri
```

## Problems with GPG keys

Sometimes the AUR package doesn't want to update (with `makepgk -sri`) because the GPG key is unknown, for example with the AUR package screencast:

```
==> Verifying source file signatures with gpg...
    screencast-1.6.0.tar.gz ... FAILED (unknown public key 019A7474297D8577)
==> ERROR: One or more PGP signatures could not be verified!
```

I solved it by importing the key manually from the ubuntu keyserver (which is supposed to be most reliable):
```
gpg --keyserver keyserver.ubuntu.com --search-keys 019A7474297D8577
```

