# Zoom teleconferencing

Download Zoom for Arch Linux from the following webpage (there is Arch version as well):
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

Update on 2.11.2023. - I decided to pull the newest version (5.16.6-1). I checkout the master branch, did the pull and built the package:
```
cd ~/src/zoom
git checkout master
git pull
makepkg -sri
```

However, again the Zoom doesn't want to even start:-( So I downgraded it again from 5.16.6-1 to 5.13.4-1 and now it works again:
```
cd ~/src/zoom
git checkout 8641821
makepkg -sri
```

Update on 7.11.2023. - Zoom doesn't work anymore! Updating to newest version over AUR doesn't work, so I tried installing it over Flatpak and it work for links at least, I can join a meeting. However, I cannot login with my Google account!

I will try installing newest version of Zoom with the first method explained (downloading the archive and installing it over pacman directly from archive). This version works normally! I just haven't tried SSO login, but Gmail login and creation of meetings works fine.

## Zoom installation over Flatpak

Install flatpak package:
```
sudo pacman -Syu flatpak
```

You can download Zoom with:
```
flatpak install flathub us.zoom.Zoom
```

You can run Zoom with:
```
flatpak run us.zoom.Zoom
```

## Zoom not working after November 2024

Zoom requires me to upgrade the client in order to work - previously I could at least join the links, and now I cannot even start it.

I tried to upgrade trhough Flatpak:
```
flatpak update us.zoom.Zoom
```

I does start but I cannot login!

They I tried to downgrade my AUR installation to 6.1.11 (the newest version 6.2 has problems as described in the AUR Zoom page):
```
cd ~/src/zoom
git checkout 0b065ca
makepkg -sri
```

But it doesn't even start:-(

So in the end I'm using the web insterface for Zoom meetings, and reformating the links as described here:
<https://wiki.archlinux.org/title/Zoom_Meetings>

    The original meeting URL:  https://<subdomain>.zoom.us/j/meeting_id?pwd=password
    Web client URL:            https://<subdomain>.zoom.us/wc/join/meeting_id?pwd=password

For meeting ID and password you need the full Zoom invitation!

There is also a web interface which replicates the desktop app and there you can just paste the original links in order to connect to meetings:
<https://app.zoom.us/wc/home>

