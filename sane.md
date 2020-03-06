# Scanning under Arch Linux

To use your scanner under Arch Linux install SANE (Scanner Access Now Easy):
```
sudo pacman -Syu xsane-gimp
```

With xsane-gimp you also get a simple frontend (xsane) and a Gimp plugin.

Another useful frontend is simple-scan:
```
sudo pacman -Syu simple-scan
```

For HP scanners there is a metapackage which already contains most of what you will need to scan (in fact, HP website considers this as de facto Linux drivers for its devices):
```
sudo pacman -Syu hplip
```

Check whether your scanner is supported:
<http://www.sane-project.org/sane-mfgs.html>

You can run one of the frontends with `xsane` or `simple-scan`, or use a command line interface.

Check whether sane recognizes your scanner: `scanimage -L`
Scan image: `scanimage --format=png --output-file test.png --progress`
Scan image with a specified device: `scanimage --device "pixma:04A91749_247936" --format=tiff --output-file test.tiff --progress`

