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

