# Rocket chat

Install Rocket.Chat from AUR:
```
git clone https://aur.archlinux.org/rocketchat-desktop.git
cd rocketchat-desktop/
makepkg -sri
```

Run the desktop application with:
```
rocket-desktop
```

## Troubleshooting

As of September 2023 I cannot run rocketchat-desktop, it reports an error:

    /usr/bin/rocketchat-desktop: line 2: exec: electron: not found

The issue and the solution is described in the AUR repository:
<https://aur.archlinux.org/packages/rocketchat-desktop>

I modified `/bin/rocketchat-desktop` file to replace `electron` with `electron22`, so the new version of the file is:
```
#!/bin/sh
exec electron22 /usr/lib/rocketchat-desktop "$@"
```

And now it works!

