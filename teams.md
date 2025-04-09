# Microsoft Teams on Arch Linux

I installed Microsoft Teams from AUR:
```
cd ~/src/
git clone https://aur.archlinux.org/teams.git
cd teams
makepgk -sri
```

You can run it with `teams`.

You can update it like any other AUR package:
```
cd ~/src/teams
git pull
makepgk -sri
```

## Retiring of Teams Linux client

Teams on Linux is being retired by Microsoft!
<https://news.ycombinator.com/item?id=32678839>

So I tried to install unofficial Teams client from AUR:
<https://aur.archlinux.org/packages/teams-for-linux>

I installed Teams for Linux from AUR:
```
cd ~/src/
git clone https://aur.archlinux.org/packages/teams-for-linux
cd teams
makepgk -sri
```

You can run it with `teams-for-linux`.

You can update it like any other AUR package:
```
cd ~/src/teams-for-linux
git pull
makepgk -sri
```

## Clearing cache

Sometimes you want to clear cache in order to sign-in with another account. You can remove (or rename) the following folders:

    /home/matija/.config/Microsoft/Microsoft Teams
    /home/matija/.config/teams
    /home/matija/.config/teams-for-linux

The last one (teams-for-linux) is what I'm using currently.

