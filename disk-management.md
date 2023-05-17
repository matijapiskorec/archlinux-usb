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

## Mounting with `mount`

Mounting the partition (specifying filesystem type is usually not neccessary as it is performed automatically):
```
sudo mount -t ntfs /dev/sdc1 /media/matija
```

Unmounting the partition:
```
sudo umount /media/matija
```

## Managing disks `udisks2` utility (instead of `mount`)

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

To only look at the main directory and not all subdirectories you can use `--max-depth` parameter:
```
du -h ~/directory --max-depth 1
```

## Making a Windows-readable USD storage drive

These are the instructions of how to convert a standard USB drive to a Windows-readable USB storage drive. Note that this will delete all partitions and all data from that disk! Plug in your external USB drive which you want to convert to Windows-readable USB storage drive, check its name with:
```
lsblk
```

Lets say its `sdb` (usually `sda` is the disk where your current OS is installed and mounted). Run `fdisk` to create partitions:
```
sudo fdisk /dev/sdb
```

Check current partitions with `p`, then delete all partitions, one by one, by typing `d` until there are no more partitions left. Now you can create a single partition with `n`, selecting all defaults which will create one partition over the whole disk.

Now you have to change the partition to NTFS/exFAT which will be readable in Windows. Type `t` and choose `7` for the partition type (you can check all partition types with `L`).

Now write `w` to write the partition and exit.

If you run `sudo parted -l` you will see that one primary partition was created. Now you have to actually format it to NTFS/exFAT. First make sure you have exfat-utils, if not you can install them with Pacman:
```
sudo pacman -Syu exfat-utils
```

Now format the primary partition on your USB storage drive as NTFS/exFAT (I'm naming the disk to Backup):
```
sudo mkfs.exfat -n Backup /dev/sdb1
```

Now you can mount the disk with udisksctl service:
```
udisksctl mount -b /dev/sdb1
```

## duc

duc – A Collection Of Tools To Inspect And Visualize Disk Usage
<https://ostechnix.com/duc-a-collection-of-tools-to-inspect-and-visualize-disk-usage/>

