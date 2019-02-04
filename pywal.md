# Automatic generation of colorschemes with pywal

Setup a color theme matching your chosen background with pywal and 50% terminal transparency:
```
sudo pacman python-pywal python-setuptools
wal -i [PATH-TO-WALLPAPER] -a 50
```

Two themes that I find visually appealing:
```
wal -i Images/1359330091856.jpg -a 95 --saturate 0.8
wal -i Images/1432908749300.jpg -a 95 --saturate 0.8
```

Pywal also has builtin themes. Check them with:
```
wal --theme
```

To setup one of the builtin themes with transparency, just run:
```
wal --theme [THEME NAME] -a 95
```

I personally prefer high contrast themes, for example: `3024`, `base16-3024`, `base16-brewer`, `base16-bright`, `base16-gruvbox-hard`, `base16-macintosh`, `base16-pico`, `base16-tube`, `sexy-tango`.

To make a theme persistent on boot add following line to `~/.xinitrc`:
```
wal -R
```

However, this does not work as expected, and so I decided to add `#include` statement in `.Xresources` that loads generated theme colors (located in `.cache/wal/`) directly:
```
#include "Themes/wal-red/colors.Xresources"
```

To list all colors available in `.Xresources`:
```
(x=`tput op` y=`printf %76s`;for i in {0..15};do o=00$i;echo -e ${o:${#o}-3:3} `tput setaf $i;tput setab $i`${y// /=}$x;done)
```

To set the same colors to tty put following in your `.bash_profile`:
```
source ~/Theme/wal-red/colors.Xresources
```

## Colorful git prompt

To include cool colored prompt with git information (idea from this [page](https://stackoverflow.com/questions/4133904/ps1-line-with-git-current-branch-and-colors)) add the following to your `.bashrc`:
```
function color_my_prompt {
    local __user_and_host="\[\033[01;32m\]\u\[\033[01;34m\]@\h"
    local __cur_location="\[\033[01;34m\]\w"
    local __git_branch_color="\[\033[31m\]"
    local __git_branch='`git branch 2> /dev/null | grep -e ^* | sed -E  s/^\\\\\*\ \(.+\)$/\(\\\\\1\)\ /`'
    local __prompt_tail="\n\[\033[35m\]>"
    local __last_color="\[\033[00m\]"
    export PS1="$__user_and_host $__cur_location $__git_branch_color$__git_branch$__prompt_tail$__last_color "
}
color_my_prompt
```

## Colorful ls command

To control the colors in ls command check following documentation:
```
man ls
man dircolors
```
