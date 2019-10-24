# Install Hyper Light Drifter on Arch Linux

Hyper Light Drifter game is a Windows/Mac/Linux game which can be purchased DRM-free over [Humble Bundle](https://www.humblebundle.com/store/hyper-light-drifter-deluxe-edition). Purchase and download an installation script, then run it:
```
sudo sh HyperLightDrifter-DRMFree-Linux-2018-11-21.sh
``` 

We are using sudo here because we will install it into `/opt` directory which is usually used for prebuilt packages by third party software distributors (for example, Sublime text).

Make a symbolic link to the run script in `/usr/local/bin` so that we can run it like any other binary:
```
sudo ln -s /opt/HyperLightDrifter/run.sh /usr/local/bin/hyperlightdrifter
```

The run script itself needs some modification now that we intend it to run outside of its local directory:
```
LD_PRELOAD=libcurl.so.3 LD_LIBRARY_PATH=/opt/HyperLightDrifter/lib:$LD_LIBRARY_PATH /opt/HyperLightDrifter/HyperLightDrifter.x86
```

We also preloaded a correct version of the libcurl library at the beginning of the line. You should now e able to run a game by simply typing from terminal (or using launcher such as dmenu):
```
hyperlightdrifter
```

The game itself depends on many 32-bit libraries which are not part of the standard Arch Linux 64-bit distribution. Officially supported Linux distribution for the game is Ubuntu, and the dependencies problem is easyly solvable there by installing the recommended packages libxcursor and ia32-libs packages. While libxcursor is avaliable on Arch (64-bit version at least), the ia32-libs is a collection of packages which on Arch are scattered far and wide. Following are the steps to install them.

First, enable the multilib pacman repository which contains 32-bit packages. Uncomment the following lines in the pacman config file `/etc/pacman.conf`:
```
[multilib]
Include = /etc/pacman.d/mirorlist
```

You will need to run `sudo pacman -S` to synchronize package cache in order to make the new packages visible.

Second, you can now install the required 32-bit packages:
```
sudo pacman -Syu lib32-libxcursor, lib32-alsa-oss, lib32-curl, lib32-gcc-libs, lib32-glu, lib32-libcurl-compat, lib32-libxrandr, lib32-libxxf86vm, lib32-openal, lib32-openssl-1.0, lib32-zlib
```

