# Destroy disk (DD)

Create an image of your USB drive which is mounted on `/dev/sdX` (check it with `fdisk -l`):
```
sudo dd if=/dev/sdX of=~/USB-image
```

To restore the image to another USB drive just invert the process (make sure the USB key is as bog or bigger than the original one): 
```
sudo dd if=~/USB-image of=/dev/sdX
```

You can also mount the image file you just created into a path without need to restore it first to another USB drive:
```
mount ~/USB-image /mnt/USB-image -o loop
```