# Sublime Text editor

Install Sublime Text editor (not available in official Arch repository):
https://www.sublimetext.com/docs/3/linux_repositories.html

Install the GPG key:
```
curl -O https://download.sublimetext.com/sublimehq-pub.gpg && sudo pacman-key --add sublimehq-pub.gpg && sudo pacman-key  --lsign-key 8A8F901A && rm sublimehq-pub.gpg
```

Select the stable channel:
```
echo -e "\n[sublime-text]\nServer = https://download.sublimetext.com/arch/stable/x86_64" | sudo tee -a /etc/pacman.conf
```

Update pacman and install Sublime Text:
```
sudo pacman -Syu sublime-text
```

Run Sublime Text with:
```
subl
```

Files can also be run with:
```
subl filename.txt
```

If you want to open a file in new window then add `-n` option:
```
subl filename.txt -n
```

Goto anything: `Ctrl+Shift+p`

Useful commands in Goto menu:
- View: Toggle Menu (hides/shows menu at the top)
- UI: Select theme (go for Adaptive)
- UI: Select color scheme (go for Monokai)
- Package Control: Install Package

Useful packages:
- Hide Menu - hide menu by default with all new instances of Sublime 

Keyboard shortcuts:
Goto anything: `Ctrl+Shift+p`
Open new tab: `Ctrl+n`
Close current tab: `Ctrl+w`
Switch between tabs: `Ctrl+[PgDn|PgUp]`
Split screen to two side-by-side regions: `Shift+Alt+2`
Remove split screen: `Shift+Alt+1`
Move a tab to one of the regions: `Ctrl+Shift+[1|2]`
