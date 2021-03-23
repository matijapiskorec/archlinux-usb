## LeoCAD for modeling Lego designs

Download LeoCAD for modeling Lego designs in Linux:
<https://www.leocad.org/download.html>

Make sure you have povray installed for rendering:
```
sudo pacman -Syu povray
```

Copy the AppImmage to `~/bin` and make is executable with `chmod +x ~/bin/LeoCAD.AppImage`.

## Wine emulation of Lego Digital Designer and Bricklink Studio

Lego Digital Designer and Bricklink Studio are available only for Windows and Mac, but can be emulated with Wine.

<https://www.lego.com/en-us/ldd>
<https://www.bricklink.com/v3/studio/download.page>

## LDCad

You can also consider LDCad which is available natively for Linux:
<http://www.melkert.net/LDCad/docs/gui>

Download latest parts from here:
<https://www.ldraw.org/parts/latest-parts.html>

Uncompress the bz2 archive in the `~/src` folder:
```
tar -xvf LDCad-1-6d-Linux.tar.bz2 -C ~/src
```

Make a symbolic link in your local bin folder:
```
ln -s /home/matija/src/LDCad-1-6d-Linux/LDCad64 /home/matija/bin/LDCad64
```

Put the downloaded parts in `~/dev/data/ldparts` and add them to the library within the LDCad program.


