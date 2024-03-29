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

If you want to force syntax highlighting on an unsaved buffer, or on a file with wrong or unfamiliar extension, you can run:
```
:set syntax=python
```

To set line numbers and nice line breaks that break at the word boundary:
```
set number
set linebreak
```

Use clipboard register `+` for all yank, delete, change and put operations  which would normally go to the unnamed register:
```
set clipboard=unnamedplus
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

I've mapped `F7` as a shortcut to open NERDTree, in `.vimrc`:
```
:map <F7> :NERDTreeToggle<CR>
```

For help just type `?` inside NERDTree.

## How to exit and save

Quit the current window / override if modified: `:q`, `:q!`
Quit all open files: `:qa`
Save the current buffer / save and quit: `:w`, `:wq`
Write only lines 10 to 20 to a separate file (ommiting the filename overwrites the current file!): `:10,20w [FILE NAME]`
Pipe the buffer to the external command: `:w ! wc -l`
Append the buffer to some other file: `:w >> [FILE]`
If the file is already open in another buffer, use this: `:w ! cat >> [FILE]`

## Windows

Create a new split window with unnamed buffer: `Ctrl+w n`
Close a window (corresponding buffer is still available!): `Ctrl+w q`
To switch between windows: `Ctrl+w w`
To move between windows: `Ctrl+w [ARROWS or hjkl movements]`
Split current window into two (horizontally): `sp` or `split` 
Split current window into two (vertically): `vs` or `vsplit` 


## Buffers

Create a split window with an unnamed buffer: `:new`
Create a vertically split window with an unnamed buffer: `:vnew`
Open an unnamed buffer in a current window: `:enew`
Open a buffer available in memory: `:b [BUFFER NAME]`
Go to next/previous buffer: `:bn,` `:bp`
Delete a buffer (close a file): `:bd`
List all available buffers in memory: `:buffers`
Set all buffers as hidden: `:set hidden`

## Tabs

Tabs are just a way of viewing buffers. Split arrangement is preserved for tabs.

Open an unnamed buffer in a new tab: `:tabnew`
Close tab: `:tabclose`
Go to next tab (in normal mode): `gt`
Go to previous tab (in normal mode): `gT`

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
Undo: u
Redo: <Ctrl-r>
 
## Shortcuts in insert mode

Delete back one character: <Ctrl-h>
Delete back one word: <Ctrl-w>
Delete back to the start of line: <Ctrl-u>
Interrupt the insert mode to insert exactly one command from the normal mode: <Ctrl-o>

### Operators

Change: c
Change the whole line: cc, S
Change the line from where you are at: C
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
Move line 1 to line 4: `:1m4`
Move current line one line down: `:m+1` `:m+`
Move current line one line up: `:m-2`
Move current line to after line 12: :m 12
Move lines 5, 6 and 7 to before first line: :5,7 0
Move lines 5, 6 and 7 to after last line: :5,7m $ 
Delete all lines matching a pattern: :g/pattern/d
Run ex command on all lines matching a pattern: g/pattern/norm i"

### Text objects

A word is a sequence of letters, digits, separated by various non-blank characters. WORD is a sequence of any characters separated by whitespaces. Following sentence "tmp/var e.g." consists of four words but only two WORDS!

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
Go up/down the display line: `gk,` `gj`
Go to the beginning/end of file: `gg`, `G`
Go to the place of last edit: `g;`
Go to first matching paren / bracket: `%`
Down to first non-blank char of line: `[count]+`
To end of line: `[count]$`
Go to the start of the next line: `+`
Go forward to the next character `C` / open parenthis `(`: `fC` / `f(`
Go back to the previous character `C` / closed parenthis `)`: `FC` / `F(`
Go forward until the next character `C` / open parenthis `(`: `tC` / `t(` 
Go back until the next character `C` / closed parenthis `)`: `TC` / `T(` 
 
Move to end of line and switch to editing mode (Append): `Shift+A`
Move to the beginning of line and switch to editing mode (Insert): `Shift+I`
Move to beginning of the line: `0`
Delete line and start editing at the beginning: `Shift+S`
Move to the end of the line: `$`

Move to line number 50: `:50`
Move to 50% of the file: `50%` (This is not an editor command - no colon at the beginning!)

### Motions in visual mode

Once you enter in visual mode by pressing `v` you have a wider range of motions.
You can move with regular motions: `w`, `W`, `hjkl`, `%`
But you can also move by text objects: `as`, `at`, `aw`, `is`, `it`, `iw`
Move to a specified line (for example, 100th): `100G`

### Block visual mode

How to select multiple lines with block wise visual mode and make changes to them:
Select block wise visual mode: `Ctrl-v`
Go down two lines: `2j`
Horizontally select to the end of the first word: `e`
Append at the end of selection: `A`
Type whatever you want: `;` or `"`
Exit visual mode: `<Esc>`

### Marks

Set mark {a-zA-Z} at current cursor position: `m{a-zA-z}`
Jump to a mark named with character a: `'a`
Jump to a previous positions: `''`
See all marks: `:marks`

## Macros

Start recording a macro and save it inder letter `a`: `qa`
Execute macro saved under letter `a` three times: `3@a`
Execute your macro again: `@@`

Some tips from Vim wiki on using macros:
<https://vim.fandom.com/wiki/Macros>

Use this mapping as a convenient way to play a macro recorded to register q: `:nnoremap <Space> @q`

Start recording keystrokes by typing qq.
End recording with q (first press Escape if you are in insert mode).
Play the recorded keystrokes by hitting space.
Suppose you have a macro which operates on the text in a single line. You can run the macro on each line in a visual selection in a single operation:

Visually select some lines (for example, type vip to select the current paragraph).
Type `:normal @q` to run the macro from register q on each line.

## Autocompletion and spelling suggestions

To autocomplete the text under the cursor in the Insert mode press `Ctrl+p` while typing.

To suggest spelling choices press `Ctrl+n` while typing.

## Registers

Registers that contains X primary selection: `"+`, `"*` 
Paste from a primary selection register: `"+p`
Copy to a primary selection register: `"+y`, `"*y`
Display registers: `:registers`, `:di`
Paste the content of the `"` register to the command line: `:<Ctrl-r>"`
Paste the content of the `+` register to the command line: `:<Ctrl-r>+`

## Surround plugin oneliners

Change double quotes to single: `csi"'`
Put double quotes on inner word: `ysiw"`
Delete double quotes: `ds"`
Sorround visual selection with double quotes: `S"`

## Vim oneliners 

Delete lines from 1 to 50: `:1,50d`
Delete one word three times: `3dw`
Delete three words one time: `d3w`
Delete two words, repeated three times: `3d2w`
Change the next match (can be repeated with .): `cgn`
Substitute all occurrences across all lines: `:%s/pattern/replacement/g`
Add a newline at all occurances of `;`: `:%s/;/\r/g`
Substitute all occurrences across all lines with confirmation: `:%s/pattern/replacement/g`
Append semicolon at the end of each line in file: `:%normal A;`
Append semicolon at the beginning of each line in file: `:%normal I;`
Delete first word after first space on each line matching pattern: `:g/pattern/norm f de`
Copy all matching lines to the end of the file: `:g/pattern/co $`
Select the previously selected area: `gv`

Copy all matching lines by appending them to register a: `:let @a='' | %g/pattern/y A`
You can then paste them by: `"ap`

Move lines that match pattern after the last line in the file: `:g/pattern/m $` 
Copy lines that match pattern after the last line in the file: `:g/pattern/co $` 
Move the line containing pattern to one line before the current cursor: `:/pattern/m-1`
Move the line preceeding the line containing pattern to one line after the current cursor: `:/pattern/-1m+1`
See all lines containing the match pattern in the temporary buffer: `:g/pattern`

All of the commands above (`m`,`co`) can be used in the visual mode on the selection - it will operate on the whole line!

Search on all lines (`%`) and replace all occurrences (`g`): `:%s/search_pattern/replace_pattern/g`
Reuse the matched pattern in the replace section by using `&`: `:%s/pattern/"&"/g`
Reference captured group with escaped brackets `\(\)`: `:%s/^\(\w*) \w*/\1/g`

Delete all lines in a file (position at the start and delete until the end): `ggdG`

Delete/change all characters until the next occurrence (but not including) of pattern: `d/pattern`, `c/pattern`

Count the number of words and characters in the visual selection: `g Ctrl-g`

Download online text file directly to the current buffer (use `<Ctrl-r>+` to paste url from primary selection register): `:r ! wget -qO- [URL]`

Count the number of matches and the number of lines where they appear: `:%s/pattern//gn`

## Execute command

Execute command allows you to execute any sequence of commands, even those that require special keys.

Find all instances of a keyword and put quotes around it: `:g/keyword/ exe "norm ni\"\eea\""`
At every line go to the end of the line, enter insert mode and then delete the last word: `:g/^/ exe "norm A\<c-w>"`
Delete the first word of every line, move to the end of line and paste it there: `:g/^/ exe "norm dw$p"`

Single quotes give you a literal string without interpretation, if you want special commands (`<Esc>` can be replaced with `\e`, `<CR>` with `\n`, `Ctrl-w` is `<c-w>`) you have to use double quotes with proper escape sequences in front of the first `<`.


## Shortcuts in the command line

Cursor to the beginning/end of command line: `Ctrl b`, `Ctrl e`
Delete word before the cursor: `Ctrl w`
Delete characters between cursor to the end of line: `Ctrl u`
Insert contents of a register: `Ctrl r` (following by the name of the register, for example `"` which is the unnamed register with the last delete/yank)
Quit command line without executing: `Ctrl c`
If incsearch is set move forward/backward through the searches while typing search: `Ctrl g`, `Ctrl t`

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

Leave only the lines containing matching pattern: `:%!grep pattern`
View only matching lines in mini buffer: `:w ! grep pattern`
Arrange text in columns using `&` as a delimiter (and Linux column command): `:%!column -s '&' -t`
Reverse the selected lines: `:'<,'>! tac`
Sort the selected lines: `:'<,'>! sort`
Out of all selected lines, leave only the ones matching the pattern: `:'<,'>! grep .txt`

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
 
The default key mapping (in the Normal mode) for the CtrlP is `Ctrl+p`. In the Insert mode the same mapping is used for autocompletion! If you want to restrict the search while using the key binding you can first `:cd` into the directory.

Switch to searching buffers: `Ctrl+f` 
Navigate the results list: `Ctrl k`, `Ctrl j`
Open the selected entry in a new tab: `Ctrl t`
Open the selected entry in a new vertical/horizontal split: `Ctrl v`, `Ctrl x` 
Submit two or more dots `..` in search entry to go up a directory.

## Remove Arch based plugins and switch to Vundle

Having vim plugins installed through plugins makes them imposible to disable as they reside in the `\usr\share\vim\` directory. We will use Vindle instead to manage all our plugins. First, remove all pacman installed plugins:
```
sudo pacman -Rns powerline-vim vim-airline vim-airline-themes vim-molokai vim nerdtree
```

Leave powerline and powerline-fonts Arch packages so that you have nice powerline statusline for other programs if needed (for example, tmux) and a patched powerline fonts which you can use with your airline vim statusline.

Clone Vundle:
```
git clone https://github.com/VundleVim/Vundle.vim.git ~/.vim/bundle/Vundle.vim
```

Add the following at the beginning of your .vimrc:
```
set nocompatible
filetype off

set rtp+=~/.vim/bundle/Vundle.vim
call vundle#begin()

Plugin 'VundleVim/Vundle.vim'

" Put all your plugins here
Plugin 'vim-airline/vim-airline'

call vundle#end()            " required
filetype plugin indent on    " required
```

You can install plugins by running: `:PluginInstall`.

## vimdiff for file differences

You can diff two files with either of these commands:
```
vim -d FILE1 FILE2
vimdiff FILE1 FILE2
```

Or, inside vim, open the two files in a split window view (ideally horizontally with `:vnew`) and then run `:windo diffthis`.

Open a file for diffing the already openned file in a vertical split window: `:vert diffs FILE`

## gvim

If you installed gvim:
```
sudo pacman -Syu gvim
```

You can edit `.gvimrc` for custom GUI-specific options. A basic setup might look something like this:
```
set guioptions-=m  "remove menu bar
set guioptions-=T  "remove toolbar
set guioptions-=r  "remove right-hand scroll bar
set guioptions-=L  "remove left-hand scroll bar
set guifont=Hack\ 9
```

## Copy search matches

Hacks to copy search matches. Unfortunatelly there is no way to execute an operation on search matches, only on lines that match the pattern (with the `:g` and `:norm`).

However, there is a simple function which you can put into your `.vimrc`:
<https://vim.fandom.com/wiki/Copy_search_matches>
```
function! CopyMatches(reg)
  let hits = []
  %s//\=len(add(hits, submatch(0))) ? submatch(0) : ''/gne
  let reg = empty(a:reg) ? '+' : a:reg
  execute 'let @'.reg.' = join(hits, "\n") . "\n"'
endfunction
command! -register CopyMatches call CopyMatches(<q-reg>)
```

After which you can use `:CopyMatches` command after any search to copy all matches.

List all lines matching the search pattern: `:g/pattern`

## Regular expressions

Non-greedy mathcing in Vim - intstead of greedy matching `.*` you can use non-greedy version `.\{-}`. For more info type `:help non-greedy`.

Find everything enclosed in square brackets: `\[.\{-}\]`

## Problems with maxmempattern

Sometimes you can get a `E363: pattern uses more memory than 'maxmempattern'` error, for example when you try to type in square bracket `[` in large Markdown files. You can check the amount of memory each variable takes with:
```
:verbose set mm? mmt? mmp?
``` 

Usually maxmempattern is 1000. You can set it to a large value:
```
:set maxmempattern=200000
```

Also, make sure you don't use square brackets as a part of text inside Markdown, they have a separate meaning in Markdown. I think you can escape them if you need with `\[` and `\]`.

## Common patterns and workflow

When I want to open a quick temprary buffer to copy/paste some text I create a new window with `Ctrl+w n`. This automatically creates a new buffer which I can immediatelly edit, and the buffer is visible in the split window bellow the current one. I can switch back to the first window with `Ctrl+w w` and switch between them as well. If I don't need a window anymore but want to keep the buffer I close the window with `Ctrl+w q`, and if I want to discard the buffer alltogether with the window I do `Ctrl+c`, which is my shortcut for forcefully destrpying the buffer.

To create a temporary buffer in a separate window (and not a split window) you have to run `:enew`.

## Encoding

Change the file encoding that is shown on the terminal: `:set encoding=utf-8`
Change the output encoding of the file that is written: `:set fileencoding=utf-8`

## Format JSON files using jq

If you have `jq` installed you can pretty-print format JSON files within vim:
```
:%!jq .
```

NOTE: As of 1.8.2022. this appears not to work anymore! Did the syntax for `jq` changed?

Set JSON syntax with:
```
:set syntax=json
```

## Run a terminal within Vim

You can run a terminal within Vim session as a separate pane:
```
:terminal
```

To exit you can just type `exit` or even close it with `Ctrl-d` if your terminal is setup that way.

## Pass a command while starting Vim

You can pass a command as an argument to Vim using either the `-c` option or the `+` syntax. For example, you can pipe the JSON from standard output to Vim and format it with an external program and set syntax highlighting using one of the following two ways:
```
| vim "+%!jq ." "+set syntax=json" -
| vim -c ":%!jq ." -c ":set syntax=json" -
```

## Change cursor based on the mode

Put this configuration in `.vimrc` in order to have different cursors in different mode:
```
" Change the cursor in different modes
" Ps = 0  -> blinking block.
" Ps = 1  -> blinking block (default).
" Ps = 2  -> steady block.
" Ps = 3  -> blinking underline.
" Ps = 4  -> steady underline.
" Ps = 5  -> blinking bar (xterm).
" Ps = 6  -> steady bar (xterm).
let &t_SI = "\<Esc>[6 q" " bar shape in insert mode
let &t_SR = "\<Esc>[4 q" " underline shape in replace mode
let &t_EI = "\<Esc>[2 q" " block shape in normal mode
if !empty($TMUX) " tmux needs special configuration for cursor
    let &t_SI = "\<Esc>Ptmux;\<Esc>\<Esc>[6 q\<Esc>\\"
    let &t_SR = "\<Esc>Ptmux;\<Esc>\<Esc>[4 q\<Esc>\\"
    let &t_EI = "\<Esc>Ptmux;\<Esc>\<Esc>[2 q\<Esc>\\"
endif
```

Update 10.6.2022. - this is not working anymore in tmux! Cursor change outside of tmuc works fine.

## Remote editing of files with Vim

You can use ssh and scp protocols to remotelly edit files with Vim. For more information see the note on Vim and the chapter `Mount remote directories with sshfs`.

Open and edit a remote file on your local machine with Vim:
```
vim scp://<HOST>//<PATH>
```

If you have a corresponding entry in `~/.ssh/config` for the server and your username you can use this:
```
vim scp://server//home/user/file.txt
```

Otherwise you have to specify full username and server URL:
```
vim scp://user@server//home/user/file.txt
```

As an alternative you can mount remote directories locally and then use Vim to edit them:
```
sshfs user@host:remote_directory local_directory
```

You can now edit directory locally and the changes will persist remotelly, and vice versa. You can unmount with fusermount3 (installed automatically with sshfs):
```
fusermount3 -u local_directory
```

As an alternative to unmounting with fusermount3 you can also unmount with the standard umount command:
```
sudo umount local_directory
```

If fusermount3 and regular umount report error that target is busy or that some other device is using the mount point, you can try lazy umount which should work:
```
sudo umount -l local_directory
```

However, as this is not a real unmount it will be impossible to remount the network disk later on! In that case a reboot of your local machine might be neccessary.

## Github copilot

You can setup Github Copilot for code completion:
<https://github.com/github/copilot.vim>

To install the plugin:
```
git clone https://github.com/github/copilot.vim.git ~/.vim/pack/github/start/copilot.vim
```

Run the Vim and setup it with: `:Copilot setup`

You will get a code which you can then enter in the provided web page. You will also have to login with your Github account and setup the payment information (first 60 days is free) and give access to the application.

Check status: `:Copilot status`

If it is enabled and online you are good to go! Use Tab to complete the code suggestions.

Check you biling information in:
<https://github.com/settings/billing>

Disable Copilot: `:Copilot disable`
Enable Copilot: `:Copilot enable`

