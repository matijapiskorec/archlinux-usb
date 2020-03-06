# Foxit reader for Arch Linux

Foxit reader is available in AUR repository, but first you have to install some AUR dependencies manually:
```
git clone https://aur.archlinux.org/gstreamer0.10.git
git clone https://aur.archlinux.org/gstreamer0.10-base.git
```

Go to each directory (in that order) and run:
```
makepkg -sri
```

Now you can clone and install Foxit reader:
```
git clone https://aur.archlinux.org/foxitreader.git
cd foxitreader
makepgk -sri
```

You can now run it with:
```
FoxitReader
```

For installation from the web page, go to the official web page, download the archive for Linux and follow the installation instructions:
```
gzip -d 'FoxitReader_version_Setup.run.tar.gz'
tar xvf 'FoxitReader_version_Setup.run.tar'
./'FoxitReader_version_Setup.run'
```

