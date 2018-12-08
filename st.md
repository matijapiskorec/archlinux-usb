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
