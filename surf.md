# Surf suckless web browser

Install surf suckless web browser with pacman:
```
sudo -Syu surf
```

You can also build it from source. First git clone the repository:
```
git clone https://git.suckless.org/surfgit clone https://git.suckless.org/surf
``` 

Now you can build it:
```
cd surf
sudo make clean install
```

If the build process fails because gcr package is missing you can install it through pacman:
```
sudo pacman -Syu gcr
``` 

## Patching surf

Make a separate directory for patches and download them with wget:
```
mkdir patches
cd patches
wget https://surf.suckless.org/patches/homepage/surf-2.0-homepage.diff
```

Apply patches:
```
git apply patches/[patch.diff]
```

If neccessary, configure surf by editing `config.h`. For example, in the case of the homepage patch the line where the HOMEPAGE variable is defined in `config.def.h` needs to be copied to `config.h`. Or you can just:
```
cp config.def.h config.h
```

Compile and install surf:
```
sudo make clean install
```

## Bookmarks

Add bookmarks to `.surf/bookmarks` file:
```
echo aldaily.com/ >> .surf/bookmarks
```

If site requires `https` connection make sure you add forward slash `/` at the end! Otherwise an `http` site will be requested!

## Tabs

Surf does not have tabs by default. However, we can use tabbed layout in our i3 window manager. As soon as you open surf execute the following i3 shortcuts on a surf window:

Define a vertical stacking of windows: `Mod v`
Define a tabbed layout for all child windows of surf: `Mod w`

Now when a surf opens a new window it will appear as a tab in i3 tabbed layout. You can switch through them with usual i3 shortcuts:

Move to the left/right tab: `Mod [arrows]`
Close a tab: `Mod Shift q`
Open a new empty window: `Mod d` (this will open a dmenu, then just type and run a new surf instance)

Only issue is that each tab acts like a separate i3 window. If you have your surf browser on one side and some other window (for example, your terminal) on other side you have to cycle through all tabs before you can reach the other window. Also, moving all of the tabs to another workspace needs to be done one by one, and your layout is not saved, so you have to reconstruct the layout in another workspace.

An alternative way to use tabs is to use tabbed, which is available in the Arch repository:
```
sudo pacman -Syu tabbed
```

You can now run surf in tabbed mode:
```
tabbed surf -e
```

Open new tab: `Ctrl Shift Return`
Previous tab: `Ctrl Shift h`
Next tab: `Ctrl Shift l`
Move selected tab to the left: `Ctrl Shift j`
Move selected tab to the right: `Ctrl Shift k`
Close tab: `Ctrl q`

Unlike using tabbed layout in i3, here all tabs act like one compact window which you can move across workspaces with standard i3 commands.


