# Migrate Arch Linux installation to another disk

We will do a [Top to Bottom](https://wiki.archlinux.org/index.php/migrate_installation_to_new_hardware) approach where we will clone the root partition of our host system to the new system, then modify configuration files where needed. The following example is for a system residing on a portable USB stick, but most steps are identical to a more standard installation on hard drive. 

First, install rsync for advanced copying:
```
sudo pacman -S rsync
```

It's maybe easier if you run all of the commands as a root user:
```
su
```

If you don't have an access to root account you will have to run all of the commands bellow with `sudo`.

Prepare the USB drive. Run `lsblk` to check exact path of type `/dev/sdX`. Partition the USB drive with `gdisk`.
```
gdisk /dev/sdX
```

First, wipe the existing partition on drive with `d` until no partitions remain. Then create three partitions with `n` and following properties:
```
n
Last sector: +10MB
Hex code: EF02

n
Last sector: +500MB
Hex code: EF00

n
```

Check the partition table with `p`, it should look something like this:
```
Number Start (sector) End (sector) Size Code Name 
1 64 20543 10.0 MiB EF02 BIOS boot partition 
2 20544 1044543 500.0 MiB EF00 EFI System 
3 1044544 62521310 29.3 GiB 8300 Linux filesystem
```

Write partitions with `w` and exit.

Format the 500MB EFI system partition with a FAT32 filesystem:
```
mkfs.fat -F32 /dev/sdX2
```

Format the Linux partition with an ext4 filesystem:
```
mkfs.ext4 /dev/sdX3
```

Mount the ext4 formatted partition as the root filesystem:
```
mount /dev/sdX3 /mnt
```

Mount the FAT32 formatted ESP partition to /mnt/boot:
```
mkdir /mnt/boot
mount /dev/sdX2 /mnt/boot
```

Before copying files you might want to set the root partition to be read-only. That way files will not be changed while we're copying files. This step is optional, in my experience it does not matter much, however it's still recommended to do:
```
mount -o remount,ro /
```

Now you can make the root partition writable again, so normal processes can continue again:
```
mount -o remount,rw /
```

rsync will work even while the system is running, but files changed during the transfer may or may not be transferred, which can cause undefined behavior of some programs using the transferred files. This approach works well for migrating an existing installation to a new hard drive or SSD. Run the following command as root (execute `su`) to make sure that rsync can access all system files and preserve the ownership:
```
rsync -aAXv --exclude={"/dev/*","/proc/*","/sys/*","/tmp/*","/run/*","/mnt/*","/media/*","/lost+found"} / /mnt/
```

By using the `-aAX` set of options, the files are transferred in archive mode which ensures that symbolic links, devices, permissions, ownerships, modification times, ACLs, and extended attributes are preserved, assuming that the target file system supports the feature. 

Generate fstab:
```
genfstab -U /mnt >> /mnt/etc/fstab
```

Ensure that the fstab is good:
```
cat /mnt/etc/fstab
```

Because you are cloning an existing system, fstab probably already contains some entries for the previous USB drive. In this case you should delete all but the last two entries. There should be two sets of mount instructions in fstab: an ext4 filesystem mounted at /, and a vfat filesystem mounted at /boot. To disable record keeping of file access times, change the mount options of the ext4 formatted partition
by changing the `relatime` option to `noatime`.

Chroot to target system:
```
arch-chroot /mnt /bin/bash
```

To configure a custom RAM disk image, edit the HOOKS variable in /etc/mkinitcpio.conf:
```
nano /etc/mkinitcpio.conf
```

Ensure the block hook comes before the filesystems hook and directly after the udev hook like the following:
```
HOOKS="base udev block filesystems keyboard fsck"
```

Now regenerate the initial RAM disk image with the changes made:
```
mkinitcpio -p linux
```

In case you have Arch Linux LTS kernel installed (check with `uname -r`) run this instead:
```
mkinitcpio -p linux-lts
```

Install the grub and efibootmgr packages (if not already installed):
```
pacman -S grub efibootmgr
```

View the current block devices to determine the target USB device with `lsblk` and note the target USB device name (without any numbers) `/dev/sdX`.

Setup GRUB for MBR/BIOS booting mode:
```
grub-install --target=i386-pc --boot-directory /boot /dev/sdX
```

Setup GRUB for UEFI booting mode:
```
grub-install --target=x86_64-efi --efi-directory /boot --boot-directory /boot --removable
```

Generate a GRUB configuration:
```
grub-mkconfig -o /boot/grub/grub.cfg
```

Exit the chroot environment:
```
exit
```

Unmount the new USB drive:
```
umount /mnt/boot /mnt
```

Powerdown the computer with `poweroff`. If you booted off a Live USB installation medium, remove it now. Powerup the computer and use the machine's boot menu to boot off your newly created Arch Linux USB. Your system should be identical to the one from which you cloned from.

If you wish, you could login to your old system from your new system (and vice versa). Simply plug in the old USB drive, mount it with:
```
sudo mount /dev/sdX /mnt
```

Then you can chroot to the old system:
```
sudo arch-chroot /mnt
```

You can then login as any of the user and start normal application, for example X server (in that case, make sure you are in tty1 terminal!):
```
su matija
startx
```

If you install and run ssh deamon on the old system, you can ssh to it!

Useful links:
[Migrate installation to new hardware](https://wiki.archlinux.org/index.php/migrate_installation_to_new_hardware)
[Copy running Linux system to other machine over network](https://softwarebakery.com/copy-linux-systems-over-network)
[Clone a Linux install to another computer](http://positon.org/clone-a-linux-system-install-to-another-computer)
[Arch Wiki rsync Full system backup](https://wiki.archlinux.org/index.php/rsync#Full_system_backup)

