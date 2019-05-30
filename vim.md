# Vim text editor

Install vim text editor:
```
sudo pacman -Syu vim
```

You can set custom themes by downloading them and then putting them in `.vim/colors/`. For example a monokai theme:
```
mkdir -p .vim/colors
cd .vim/colors
wget https://raw.githubusercontent.com/sickill/vim-monokai/master/colors/monokai.vim
```

You can enable the them by putting the following in your `.vimrc`:
```
syntax enable
colorscheme monokai
```

To set line numbers and nice line breaks that break at the word boundary:
```
set number
set linebreak
```

## NERDTree plugin

NERDTree plugin gives a filesystem viewer on a sidebar. You can install it through pacman:
```
sudo pacman -Syu vim-nerdtree
```

And run it within vim with:
```
:NERDTree
```

To switch between windows: `Ctrl+ww`

## Powerline and Airline status line

To install airline status line:
```
sudo pacman -Syu vim-airline vim-airline-themes
```

To install powerline status line:
```
sudo pacman -Syu powerline powerline-fonts powerline-vim
```

To enable it add this to `.vimrc`:
```
set laststatus=2
let g:powerline_pycmd="py3"
let g:airline_theme="dark"
let g:airline_powerline_fonts=1
let t_Co=256
```

## fzf fuzzy file finder

If you have fzf fuzzy file finder you probably already installed vim fzf plugin as an optional dependency. You can use `:FZF` command to search files and folder in the current directory, or add path to search, for example:
```
:FZF doc/note/evernote/
```

## Reading from stdin

Vim can read text from standard input. Just supply it with `-` as an argument instead of the actual file. For example:
```
ls | vim -
```
