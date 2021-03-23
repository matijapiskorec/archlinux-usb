# Manage clipboard through clipmenu

Install `clipmenu` and optional dependency `clipnotify`:
```
sudo pacman -Syu clipmenu
sudo pacman -Syu --asdeps clipnotify
```

Run and enable `clipmenud` service on startup:
```
systemctl --user enable clipmenud
systemctl --user start clipmenud
```

Run `clipmenu` to select a clipboard entry:
```
clipmenu
```

In i3, you can bind this to the key combination by putting following line in `~/.config/i3/config`:
```
bindsym $mod+Shift+d exec clipmenu
```

In terminal you can copy by selecting text.
In micro you can copy by `Ctrl-C`.
In terminal and micro you can paste it with `Shift Insert`.

Don't forget to run clipmenu to select what you want before you paste!

To clear all entries from the clipboard:
```
clipdel -d ".*"
```

## Troubleshooting

Somewhere in 2020 clipmenu stopped working - the daemon is running but no results are ever stored! I tried running journalctl to see error messsages regarding clipmenu:
```
journalctl -b | grep clipmenu
```

It reports "ERROR: The X dsiplay is unset, is your X server running?". When I run clipmenu from the terminal (as opposed from the dmenu selector) the error message is related to a cache file. This discussion suggests that the problem could be in the missing DISPLAY environment variable in the service configuration:
<https://bugs.archlinux.org/task/68288>

So I added:
```
Environment=DISPLAY=:0
```

In the Service section of the `~/.config/systemd/user/default.target.wants/clipmenud.service`. Restarted the clipmenu service and now everything works fine!

