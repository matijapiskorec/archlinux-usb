# Zoom teleconferencing

Download Zoom for Arch Linux from the following webpage:
<https://us04web.zoom.us/support/down4j>

Follow instructions for installation:
<https://support.zoom.us/hc/en-us/articles/204206269-Installing-or-updating-Zoom-on-Linux>

In brief, position to the folder where you downloaded the archive, then run (make sure to check the exact extension of archive!):
```
sudo pacman -U zoom_x86_64.pkg.tar.tar
```

Follow the same procedure when you update Zoom.

To uninstall Zoom run the following:
```
sudo pacman -Rs zoom
```

This will also remove all dependencies which are not needed by some other application.

