# Playing original Diablo game on Linux

DevilutionX is a Diablo build for modern operating systems:
<https://github.com/diasurgical/devilutionX>

Download prebuilt devilutionx binaries:
```
wget https://github.com/diasurgical/devilutionX/releases/download/0.4.0/devilutionx-linux-i386.tar.xz
```

Extract the files:
```
mkdir devilutionx
tar xf devilution-linux-i386.tar.xz
```

Make sure you have libsdl2, libsdl2-mixer and libsdl2-ttf installed. In Arch Linux these are available in the following packages:
```
extra/sdl2
extra/sdl2_mixer
extra/sdl2_ttf
```

And for the 32-bit versions:
```
multilib/lib32-sdl2
multilib/lib32-sdl2-mixer
multilib/lib32-sdl2-ttf
```

Compiling devilutionx from source is more involved and requires cmake and other libraries to be installed, it's maybe the best just to use the prebuilt binary.

Copy the `diabdat.mpq` from your Diablo CD or a GoG installation to the devilutionx directory. Make sure everything is lower case! Then just run the game with:
```
./devilutionx
```

For easier runnning you can create a symlink in an apropriate bin directory:
```
sudo ln -s $HOME/src/devilutionx/devilutionx /usr/local/bin/diablo
```

Configuration file and saved games are installed in `~/.local/share/diasurgical/devolution/`. You can modify `diablo.ini` to start in windowed instead of fullscreen mode by setting `fullscreen=1` option to `fullscreen=0`.

To get `DIABDAT.MPQ` you have to first install the game via Wine on Linux. However, it is possible to unpack this file from the `.exe` installation file using innoextract extractor, which unpacks installers created with Inno Setup on Windows:
<http://constexpr.org/innoextract/>

For a full guide of how to install Diablo from GoG without using Wine see this guide:
<https://www.gog.com/forum/diablo/playit_install_diablo_on_linux/post1>

Although GOG version does not work in Wine on my Arch Linux 64 bit setup, it seems that running from the mod directly works fine with Wine! Download the mod from here and extract it somewhere where Wine can see it:
<https://mod.diablo.noktis.pl/download>

Copy `DIABDAT.MPQ` as `diabdat.mpq` into the game directory. Now you can run mod's executable with wine to run the game!
```
wine .wine/drive_c/GoG Games/DiabloMod/Tchernoborg.exe
```

If you have SFX initialization error you can fix in in the following way. Download Win32 and Win64 binaries from:
<https://kcat.strangesoft.net/openal.html>

Extract the `openal-soft-1.19.1-bin/bin/Win32/soft_oal.dll` into the game directory and rename it to `wrap_oal.dll`. Game should run fine with Wine now!

You can even play it in the browser! In that case you can use your own mpq file instead of playing a shareware version:
<https://d07riv.github.io/diabloweb/>

For a similar implementation of Nox, see here:
<https://playnox.xyz/>

You can also try to install it using Lutris, which is available in the Arch community repository. Pros - there are many automatic install scripts, some of which integrate popular mods which give you high resolution support and new content. For example these two:
<https://www.gog.com/forum/diablo/play_diablo_on_linux>
<https://github.com/legluondunet/MyLittleLutrisScripts/tree/master/Diablo>

Cons - you need to create a Lutris account. Maybe you can follow the above install script and install the mod yourself? The webpage of the mod:
<https://mod.diablo.noktis.pl/>

## Sound problems

At some point the sound suddenly stopped until I installed `lib32-libpulse`:
```
sudo pacman -Syu lib32-libpulse
```

