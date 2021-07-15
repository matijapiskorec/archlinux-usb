# ranger terminal filesystem manager

Install ranger:
```
sudo pacman -S ranger
```

Commands in ranger:
Quite ranger: `Q`
Reload current directory: `R`
Open file with: `r`
Change sort order: `o`
View hidden files: `zh`
Rename current file: `cw`
Select file: `space`
Yank/copy file: `yy`
Yank/copy file name: `yn`
Yank/copy file path: `yp`
Paste: `pp`
Cut: `dd`
Delete: `dD`
Search for files: `/`
Execute range command: `:`
Execute shell command: `!`
Change file permissions: `chmod`
Disk usage current directory: `du`
Create a new tab: `Ctrl-n`
Close current tab: `Ctrl-w`
Next/previous tab: `Tab / Shift-Tab`
Mark/unmark a file: `Space`
Unmark all files in folder: `uv`

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

To setup a custom colorscheme, put the colorscheme config in `~/.config/ranger/colorschemes`. Use the template for the default theme [here](https://github.com/ranger/ranger/blob/master/ranger/colorschemes/default.py). Then set the colorscheme by running `:` inside ranger and then typing:
```
set colorscheme [NAME OF YOUR .PY COLORSCHEME]
```

To make it permanent at startup put it in `.config/ranger/rc.conf` file.

## Troubleshooting

I decided to turn off file preview in `.config/ranger/rc.conf`:
```
set preview_files false
```

The reason for this is that I had problem with previewing large files and large archives, for example gzip archives. Apparently ranger file preview uses bsdtar to preview archive files and has large memory footprint - running file preview in ranger while compressing large 11 GB file took almost 7 GB of memory! Turning off file preview made gzip compression much faster and with almost zero memory footprint!

