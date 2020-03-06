# Photo manegement in Arch Linux

To import photos from a digital camera install libghoto2 (library) and gphoto2 (cli interface), and optionally darktable (photo editor):
```
sudo pacman -Syu libgthoto2 gphoto2 darktable
```

You can then use darktable GUI interface to import photos from your digital camera. Optionally, you can use gphoto2 in terminal. For example, to detect your camera:
```
gphoto2 --auto-detect
```

To list files on camera:
```
gphoto2 --list-files
```

To get files 7 to 13 from the list output by the above command:
```
gphoto2 --get-file 7-13
```

To get all files from the camera:
```
gphoto2 --get-all-files
```

## Using ImageMagick for photo manipulation

Extract EXIF information from a photo:
```
identify -verbose [PHOTO]
```
