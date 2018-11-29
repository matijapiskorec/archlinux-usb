# Installing and configuring dwm window manager

Clone and install `dwm` (dynamic window manager):
```
git clone git://git.suckless.org/dwm
cd dwm
make clean install
```

And then run it with (or put it in `.xinitrc`):
```
exec dwm
```

Cheatsheet:

Launch terminal: `Shift Alt Enter`
dmenu for running programs: `Alt p`
Toggle windows bewteen master and stack: `Alt Enter`
Move to another terminal: `Alt [j|k]`
Move terminal to another tag: `Shift Alt [number]`
Focus on another tag: `Alt [number]`
Kill a window: `Shift Alt c`