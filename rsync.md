# Synchronize directories with rsync

Copy (synchronize) remote folder to local over ssh:
```
rsync -avzhe ssh --progress user@server:~/folder .
```

Copy (synchronize) local folder to remote over ssh:
```
rsync -avzhe ssh --progress /folder user@server:~/folder
```

If your destination directory has some files which are not in source, by default they will remain. Use `--delete` option to delete them at the destination directory also. Following command will copy files from remote to local, making sure to delete local files which are not on remote:
```
rsync -avzhe ssh --progress --delete user@server:~/folder .
```

You can always add a dry run option `--dry-run` which will output results without actually copying anything.

## Synchronizing with an Arch Linux installation on USB drive

First, check and mount the usb drive, main partition (`/dev/sdX3`) to `/mnt` and boot partition (`/dev/sdX2/`) to `/mnt/boot`:
```
lsblk
sudo mount /dev/sdX3 /mnt
sudo mkdir /mnt/boot
sudo mount /dev/sdX2 /mnt/boot
```

Then, copy the whole root partition to USB with rsync, in archive mode but excluding some machine-specific directories, including `/etc/fstab` and `/boot`:
```
sudo rsync -aAXv --exclude={"/dev/*","/proc/*","/sys/*","/tmp/*","/run/*","/mnt/*","/media/*","/lost+found","/etc/fstab","/boot/*"} --delete / /mnt
```

In case there are some changes to `/boot` folder, for example after a kernel upgrade, you have to additionally run following commands so that the boot configuration is rebuilt on the USB drive:
```
arch-chroot /mnt mkinitcpio -p linux
arch-chrott /mnt grub-mkconfig -o /boot/grub/grub.cfg
```

You can now unmount the USB drive. When you boot from it, it should boot to the equivalent system!
```
sudo umount /mnt/boot /mnt
```
