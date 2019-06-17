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

## Installing the sorround plugin manually

surround.vim: quoting/parenthesizing made simple
<https://github.com/tpope/vim-surround>

Use vim's built-in package support to install sorround package:
```
mkdir -p ~/.vim/pack/tpope/start
cd ~/.vim/pack/tpope/start
git clone https://tpope.io/vim/surround.git
vim -u NONE -c "helptags surround/doc" -c q
```

## Vim reference

Insert Mode: i, a, c
Visual Mode: v, V, <Ctrl-v>
Command-line Mode: :, /
Show status line indicating file name: <Ctrl-g>
Scroll down/up half a screen: <Ctrl-d>, <Ctrl-u>
 
### Operators

Change: c
Change the whole line: cc
Delete: d
Delete the whole line: dd
Swap case: ~
Make lowercase: gu
Make uppercase: gU
Filter to external program: !
Shift left: <
Shift right: >
Indent: =
Repeat the last command: .
Yank (copy): y
Yank the whole line: yy, Y
Paste: p
Join lines: J

### Text objects

A word is a sequence of letters, digits, separated by various non-blank characters. WORD is a sequence of any characters separated by whitespaces.
Following sentence "tmp/var e.g." consists of four words but only two WORDS!

A word: aw
Inner word: iw
A WORD: aW
Inner WORD: iW
A paragraph: ap
Inner paragraph: ip
A bracket: ab
Inner bracket: ib
A tag block: at
Inner tag block: it
A sentence: as
Inner quotes: i"

### Motions

Go forward by a word/WORD (beginning): w, W
Go forward by a word/WORD (end): e, E
Go backward by a word/WORD: b, B
Go down: j
Go up: k
Go left: h
Go right: l
Go up/down the display line: gk, gj
Go to first matching paren / bracket: %
Down to first non-blank char of line: [count]+
To end of line: [count]$

Move to end of line and switch to editing mode (Append): Shift+A
Move to the beginning of line and switch to editing mode (Insert): Shift+I
Move to beginning of the line: 0
Delete line and start editing at the beginning: Shift+S
Move to the end of the line: $

## Vim oneliners 

Change double quotes to single with the surround plugin: ci"'
Delete one word three times: 3dw
Delete three words one time: d3w
Delete two words, repeated three times: 3d2w

## Reading from a shell

Read an output from a command from shell:
```
:r ! ls ~
```

Pipe the current buffer to the external command:
```
:w ! wc
```

Sort the current buffer in place:
```
:%!sort
```


