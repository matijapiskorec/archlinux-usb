# Mounting iPhone on Arch Linux with ifuse

First, install ifuse package:
```
sudo pacman -Syu ifuse
```

Make sure that you have the fuse module loaded by running (you can put it in your `/etc/modules-load.d`):
```
sudo modprobe fuse
```

Now you can mount your iPhone:
```
ifuse [MOUNT-POINT]
```

And unmount it with:
```
umount [MOUNT-POINT]
```

## Package moved to AUR

It seems that package moved to AUR since some time (I noticed this in October 2020). It is available in my Pacman, but not in the repositores, so I just installed it again from the AUR:
```
cd ~/src
git clone https://aur.archlinux.org/ifuse.gi://aur.archlinux.org/ifuse.git
cd ifuse
makepg -sri
```

I can confirm that I have the new installation by running:
```
pacman -Qi ifuse
```

This also fixed problems that I had previously! For some reason the old version of ifuse did not work with my iPhone anymore!

