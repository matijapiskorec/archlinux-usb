# Polybar as a replacement for i3 status bar

Clone a package from Github:
```
git clone https://github.com/jaagr/polybar.git (stable version)
git clone https://github.com/jaagr/polybar-git.git (development version)
```

Install a package (-i) and missing dependencies (-s) and remove them at the end (-r):
```
cd polybar
makepkg -sri
```

Removing a package with pacman is the same as with regular packages:
```
sudo pacman -R polybar
```

In case of polybar, make sure you also install a jsoncpp dependency:
```
sudo pacman -S jsoncpp
```

Sometimes there are still problems with missing dependencies for `libjsoncpp.so`:
```
Error reported is "polybar: error while loading shared libraries: libjsoncpp.so.19: cannot open shared object file: no such file or directory". 
```

That's because it's lib files change names on each new update. If that happens it is generally recommended to recompile polybar after each jsoncpp update. In case there are still problems you can also add symlink to the correct version:
```
ln -s /usr/lib/libjsoncpp.so.20 /usr/lib/libjsoncpp.so.19
```

Install example polybar configuration:
```
install -Dm644 /usr/share/doc/polybar/config ~/.config/polybar/config
```

And run it with:
```
polybar example
```

Run it so that it reloads as soon as you change configuration:
```
polybar -r example
```

To specify a monitor on which to run:
```
MONITOR="DVI-I-2" polybar example
```

Setup polybar on startup:
https://github.com/jaagr/polybar/wiki

Cool polybar theme:
https://github.com/nicomazz/i3-polybar-config

Remove i3 bar by commenting out this line in `~/.config/i3`:
```
bar {
	status_command i3status
}
```

And adding following line which executes launch script:
```
exec_always --no-startup-id $HOME/.config/polybar/launch.sh
```

Usually you could just reload the i3 config with `$mod+Shift+c` but because you modified status bar you have to restart it with `$mod-Shift-r`. Before you do, make sure you close all the open windows (easiest with `$mod-Shift-q` on each window).

