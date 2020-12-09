# Disk management in Linux

List current disk usage by partition:
```
df -h
```

List block devices, which effectivelly gives you all mounted and unmounted drives available to the system:
```
lsblk
```

For more informative output that also includes filesystem type, UUID, SIZE and LABEL:
```
lsblk -f -o +SIZE
```

# Mounting with `mount`

Mounting the partition (specifying filesystem type is usually not neccessary as it is performed automatically):
```
sudo mount -t ntfs /dev/sdc1 /media/matija
```

Unmounting the partition:
```
sudo umount /media/matija
```

# Managing disks `udisks2` utility (instead of `mount`)

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

Install `ncdu` simple disk usage analyzer:
```
sudo pacman -Syu ncdu
```

Disk usage for a given file or directory: `du -sh [path|file|dir]`
Disk usage for a given file or directory, along with total: `du -shc [path|file|dir]`

## File and directory size

To check a directory size run du utility (this will also check sizes of all subdirectories):
```
du -h ~/directory
```

