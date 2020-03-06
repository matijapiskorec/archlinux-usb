# Simple terminal (ST)

Clone st and some patches:
```
git clone git://git.suckless.org/st
cd st
mkdir patches
cd patches
wget https://st.suckless.org/patches/alpha/st-alpha-20180616-0.8.1.diff
```

Apply patches:
```
patch < patches/[patch.diff]
```

Configure st by editing `config.h`.

Compile and install:
```
sudo make clean install
```

You can now run st with:
```
st
```

To change colors with pywal, remove all color definitions in your `config.h` (this includes `defaultfg`, `defaultbg` and others). Also, remove `const char *colorname[]` array and on the same place include wal's export colors via:
```
#include "/home/matija/themes/wal-blue/colors-wal-st.h"
```

You can now recompile st in the same way as above.

## LukeSmith version of st

Luke Smith made a preconfigured st version with many usefull patches. You can install it in the following way:
```
git clone https://github.com/LukeSmithxyz/st
cd st
sudo make install
```

Scroll in terminal: `Alt-[j|k]` or `Alt-[up|down]`
Change font size with: `Alt-Shift-[j|k]` or `Alt-Shift-[up|down]`

Default font size and alpha transparency is set in your Xresources file, for example like this:
```
st.font: Hack:pixelsize=12:antialias=true:autohint=true;
st.alpha: 0.95
```

Don't forget to restart your Xresources with xrdb (and open a new terminal!):
```
xrdb ~/.Xresources
```

## Problems with tmux

If you have problems with tmux and vim under st - for example exiting vim under tmux exits the current session as well, this is the solution. If you did not install st with make clean install, you must compile the st terminfo entry with the following command (within the st source folder):
```
tic -sx st.info
```

This will create `~/.terminfo` folder with relevant data.

