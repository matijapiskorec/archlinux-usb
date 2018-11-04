# Mounting a RAM disk in Arch

Make a folder where your RAM disk will be:
```
sudo mkdir -p /media/ramdisk
```

Mount a RAM disk with maximum size of 2GB:
```
sudo mount -t tmpfs -o size=2048M tmpfs /media/ramdisk
```

RAM disk will be cleared after reboot. If you want it to persist after boot add the following to your `/etc/fstab`:
```
none /media/ramdisk tmpfs nodev,nosuid,noexec,nodiratime,size=2048M 0 0
```

You can test the newly modified `fstab` with `mount -a`. If there are no warnings you are good to go.

To unmount the RAM disk:
```
sudo umount /media/ramdisk
```
