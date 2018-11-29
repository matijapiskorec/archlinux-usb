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

