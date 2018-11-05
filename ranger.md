# ranger terminal filesystem manager

Install ranger:
```
sudo pacman -S ranger
```

Commands in ranger:
Quite ranger: `Q`
Reload current directory: `R`
Open file with: `r`
Change sort order: `O`
View hidden files: `zh`
Rename current file: `cw`
Select file: `space`
Yank/copy: `yy`
Paste: `pp`
Search for files: `/`
Execute range command: `:`
Execute shell command: `!`
Change file permissions: `chmod`
Disk usage current directory: `du`
Create a new tab: `Ctrl-n`
Close current tab: `Ctrl-w`
Next/previous tab: `Tab / Shift-Tab`

Additional dependencies needed for viewing certain file formats:
```
w3m poppler ffmpegthumbailer elinks atool
```

For viewing images in ranger install w3m:
```
sudo pacman -S w3m
```

Copy all ranger configuration files in your home folder so that you can mess around with them:
```
ranger --copy-config=all
```

Configuration files are now in `~/.config/ranger/`, edit `rc.conf`:
```
set preview_images true
set preview_images_method w3m
```

To allow PDF preview uncomment following lines in `.config/ranger/scope.sh`:
```
application/pdf)
    pdftoppm -f 1 -l 1 \
             -scale-to-x 1920 \
             -scale-to-y -1 \
             -singlefile \
             -jpeg -tiffcompression jpeg \
             -- "${FILE_PATH}" "${IMAGE_CACHE_PATH%.*}" \
        && exit 6 || exit 1;;
```