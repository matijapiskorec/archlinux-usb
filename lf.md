# Simple file management in terminal with lf

Install lf through AUR:
```
git clone https://aur.archlinux.org/lf.git
cd lf
makepkg -sri
```

Copy a template configuration file:
```
mkdir -p ~/.config/lf
curl https://raw.githubusercontent.com/gokcehan/lf/master/etc/lfrc.example -o ~/.config/lf/lfrc
```

Run it with:
```
lf
```

Reference:
Up/down: `j/k`
Up/down directory structure: `h/l`
Select: `<space>`
Invert selection: `v`
Unselect all: `u`
Copy selection: `y`
Cut: `d`
Paste: `p`
Clear copied selection: `c`
Show hidden files: `zh`
Sort by time: `st`
Sort by size: `ss`
Rename: `r`
Edit in editor: `e`

