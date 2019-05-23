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
Split screen to [two|three] side-by-side panels: `Shift+Alt+[2|3]`
Split screen to [two|three] vertical panels: `Shift+Alt+[8|9]`
Switch to panel [one|two]: `Ctrl+[1|2]`
Remove split screen: `Shift+Alt+1`
Move a tab to one of the panels: `Ctrl+Shift+[1|2]`

## Piping to Sublime

Unfortunatelly, you cannot pipe directly to Sublime in order to edit text. For this you can use vipe program from moreutils:
```
sudo pacman -Syu moreutils
```

You have to set your EDITOR variable to Sublime (for example, in `.bashrc`):
```
export EDITOR='subl --wait'
```

Now you can pipe to Sublime:
```
ls | vipe
```

Pipe output will be in a temporary file, you can modify and change the content of the pipe, as soon as you close the file the pipe will continue, so in the example above it will output to your terminal. This means you can also use vipe in the middle of the pipe:
```
ls | vipe | cat
```

As an alternative, you can always pipe to xclip clipboard selection and then paste it manually to Sublime:
```
ls | xclip -selection clip
```
