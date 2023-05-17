# Zoom teleconferencing

Download Zoom for Arch Linux from the following webpage:
<https://us04web.zoom.us/support/down4j>

Follow instructions for installation:
<https://support.zoom.us/hc/en-us/articles/204206269-Installing-or-updating-Zoom-on-Linux>

In brief, position to the folder where you downloaded the archive, then run (make sure to check the exact extension of archive!):
```
sudo pacman -U zoom_x86_64.pkg.tar.xz
```

Follow the same procedure when you update Zoom.

To uninstall Zoom run the following:
```
sudo pacman -Rs zoom
```

This will also remove all dependencies which are not needed by some other application.

## Update Zoom installation from AUR

If you installed Zoom through AUR then you follow the standard procedure for updating the AUR package:
```
cd ~/src/zoom
git pull
makepkg -sri
```

## Zoom breaking on 5.13.5 upgrade

Zoom doesn't run after 5.13.5 upgrade! I had to downgrade it to 5.13.4 but then SSO login doesn't work! So I have to use my gmail login. Also, links to meetings probably also don't work, but I have to test this!

Currently (21.3.2023.) Zoom is at 5.14.0, but I had to downgrade to 5.13.4 with git:
```
cd ~/src/zoom
git checkout 8641821
makepkg -sri
```

When I tried 5.13.5 it didn't want to launch at all!
```
cd ~/src/zoom
git checkout 8641821
makepkg -sri
```

Once this issue is resolved in new version, I can just checkout the master branch and upgrade to the newest version:
```
cd ~/src/zoom
git checkout origin/master
makepkg -sri
```

