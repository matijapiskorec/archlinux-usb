# Lakka retro gaming console on live usb

Lakka is a retro gaming console system based on Arch Linux. You can run it from a live bootable usb on a regular PC. First, prepare the live USB drive. Check the name of the drive:
```
lsblk
```

Format the drive with fdisk:
```
fdisk /dev/sdX
```

Execute following commands:
`d` until there are no partitions
`n` for new partition
`t` for new type
`6` for Lenovo boot partition (?)
`w` for writting changes to disk

Format the drive to fat32 file system:
```
mkfs.fat -F32 /dev/sdX2
```

Check if everything is ok:
```
lsblk -f -o +SIZE
```

Flash the Lakka image to USB drive:
```
sudo dd if=Lakka-Generic.x86_64-2.2.img of=/dev/sdX status=progress
```

Unmnount the live usb and poweroff the computer. Plug only the Lakka live usb and let it build the filesystem and boot Lakka. Now you can again poweroff the Lakka system and return to your main system for additional configuration. 

You are now ready to put BIOSes and ROMs on your Lakka live usb. You have to mount the second partition of the live usb in order to access the Lakka filesystem.
```
lsblk
udisksctl mount -b /dev/sdX2
```

BIOSes go to `system/`, ROMs go to `roms`. You need three BIOSes:
```
scph5500.bin
scph5501.bin
scph5502.bin
```

You can check checksums to match those at [BIOSes](http://www.lakka.tv/doc/BIOSes/) and [Playstation](http://www.lakka.tv/doc/PlayStation/) pages in Lakka documentation:
```
md5sum -b SCPH5500.BIN
```

Once you download ROMs, they are probably compressed in either 7z, zip or rar formats. Install required decompressers:
```
sudo pacman -Syu unrar
sudo pacman -Syu p7zip 
```

Now you can decompress rar and 7z archives:
```
unrar x [ROM.TAR] roms/
7z e [7Z COMPRESSED ROM]
```

Once you decompress the ROM archives, the bin image is probably in ecm compressed format. Before you put it on Lakka live usb you have to decompress it as well:
```
sudo pacman -Syu ecm-tools
ecm2bin [ROM IN BIN.ECM COMPRESSED FORMAT]
```

You can convert img/ccd to bin/cue format with Poweriso:
```
wget http://www.poweriso.com/poweriso-1.3.tar.gz
tar xvzf poweriso-1.3.tar.gz -C poweriso/
./poweriso convert [IMG FILE] -o [BIN FILE] -ot bin
```

## Lakka HDMI configuration

You can connect to the HDMI output through the Lakka video options by changing the display. Sound will probably not switch automatically, for this you need to manually type in the sound output. Typing `hdmi` worked on my system.

If you don't want to use keyboard while having the HDMI output you can use controller for all input, including exiting the game to a main interface - just press `L3` and `R3` at the same time (these are middle joystick sticks which can be pressed as well as moved around).

## RetroArch

Lakka is built on top of RetroArch:
<https://www.retroarch.com/>
<https://wiki.archlinux.org/index.php/RetroArch>

You can install RetroArch on you system (the last two are for nicer GUI):
```
sudo pacman -Syu retroarch retroarch-assets-xmb retroarch-assets-ozone
```


