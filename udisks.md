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