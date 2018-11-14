# Manage disks with modern udisks2 utility (instead of mount)

Install udisks2 package:
```
sudo pacman -S udisks2
```

View help and available disks on the system:
```
udisksctl help
udisksctl dump
```

Mount a desired disk (in this case, just a specific partition within a disk!):
```
udisksctl mount -b /dev/sda2
```

Disk is now mounted in `/run/media/matija/` and user can access it normally.

To unmount it:
```
udisksctl unmount -b /dev/sda2
```

In order to write to a NTFS volume (Windows filesystem) you need to install `ntfs-3g` package, as Arch Linux only support reading from NTFS:
```
sudo pacman -Syu ntfs-3g
```
