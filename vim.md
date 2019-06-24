# Vim text editor

Install vim text editor:
```
sudo pacman -Syu vim
```

However, in this way you will not get xorg clipboard support which is only available by installing gvim package which, in addition to standard vim cli editor also contains gvim GUI editor. The only downside is the installation of (potentially unneccessary) gtk libraries. To install gvim package:
```
sudo pacman -Syu gvim
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
## How to exit and save

Quit the current window / override if modified: `:q`, `:q!`
Save the current buffer / save and quit: `:w`, `:wq`
Write only lines 10 to 20 to a separate file (ommiting the filename overwrites the current file!): `:10,20w [FILE NAME]`
Pipe the buffer to the external command: `:w ! wc -l`

## Windows

Create a new window: `Ctrl+w n`
Close a window (corresponding buffer is still available!): `Ctrl+w q`
To switch between windows: `Ctrl+w w`
To move between windows: `Ctrl+w [ARROWS or hjkl movements]`

## Buffers

Create a split window with an unnamed buffer: `:new`
Create a vertically split window with an unnamed buffer: `:vnew`
Open an unnamed buffer in a current window: `:enew`
Open an unnamed buffer in a new tab: `:tabnew`
Open a buffer available in memory: `:b [BUFFER NAME]`
Go to next/previous buffer: `:bn,` `:bp`
Delete a buffer (close a file): `:bd`
List all available buffers in memory: `:buffers`

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

## Installing the surround plugin manually

surround.vim: quoting/parenthesizing made simple
<https://github.com/tpope/vim-surround>

Use vim's built-in package support to install surround package:
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
Move current line one line down: :m+1, :m+
Move current line one line up: :m-2
Move current line to after line 12: :m 12
Move lines 5, 6 and 7 to before first line: :5,7 0
Move lines 5, 6 and 7 to after last line: :5,7m $ 
Delete all lines matching a pattern: :g/pattern/d
Run ex command on all lines matching a pattern: g/pattern/norm i"

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
A quotes: a"
Inner curly braces: i}
A curly braces: a} 

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

## Autocompletion and spelling suggestions

To autocomplete the text under the cursor in the Insert mode press Ctrl+p while typing.

To suggest spelling choices press Ctrl+n while typing.

## Registers

Registers that contains X primary selection: "+, "* 
Paste from a primary selection register: "+p
Display registers: :registers, :di

## Surround plugin oneliners

Change double quotes to single: csi"'
Put double quotes on inner word: ysiw"
Delete double quotes: ds"
Sorround visual selection with double quotes: S"

## Vim oneliners 

Delete one word three times: 3dw
Delete three words one time: d3w
Delete two words, repeated three times: 3d2w
Change the next match (can be repeated with .): cgn
Substitute all occurrences across all lines: :s/pattern/replacement/g
Substitute all occurrences across all lines with confirmation: :s/pattern/replacement/g
Append semicolon at the end of each line in file: :%normal A;
Append semicolon at the beginning of each line in file: :%normal I;
Delete first word after first space on each line matching pattern: :g/pattern/norm f de
Copy all matching lines to the end of the file: :g/pattern/co $

Copy all matching lines by appending them to register a: :let @a='' | %g/pattern/y A
You can then paste them by: "ap

## Reading from a shell

Read an output from a command from shell:
```
:r ! ls ~
```

Pipe the current buffer to the external command:
```
:w ! wc
```

For example, curl a cheat sheet from `cht.sh` service (with additional stripping of the color codes with sed):
```
:r ! curl cht.sh/python/lambda | sed 's/\x1b\[[0-9;]*m//g' 
```

Sort the current buffer in place:
```
:%!sort
```

Leave only the lines containing matching pattern: :%!grep pattern
View only matching lines in mini buffer: :w ! grep pattern

## CtrP fuzzy file finder

Install CtrlP fuzzy file finder plugin:
```
cd ~/.vim
git clone https://github.com/ctrlpvim/ctrlp.vim.git bundle/ctrlp.vim
```

Add to your .vimrc:
```
set runtimepath^=~/.vim/bundle/ctrlp.vim
```

You can now use `:CtrlP` command to fuzzy search the current directory or supply a path to search the subdirectory.
 
The default key mapping (in the Normal mode) for the CtrlP is Ctrl+p. In the Insert mode the same mapping is used for autocompletion! If you want to restrict the search while using the key binding you can first `:cd` into the directory.

