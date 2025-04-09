# Fish friendy interactive shell

Install fish friendly interactive shell:
```
sudo pacman -Syu fish
```

To enter fish shell just type:
```
fish
```

To customize your prompt, define a `fish_prompt` function in `~/.config/fish/functions/fish_prompt.fish`:
```
function fish_prompt --description 'Write out the prompt'
	set_color -o E51A1A
	echo -n -s "$USER"
	set_color 4B96EB 
	echo @(prompt_hostname) (pwd)
	echo -n -s '> '
	set_color normal
end
```

Most fish configuration could be done in browser by running:
```
fish_config
```

## Setting fish as a default interactive shell

You can set fish as a default interactive shell instead of bash by modifying your `.bashrc` to include as the last command:
```
exec fish
```

In this way fish will replace bash process as soon as it starts, and exiting the fish shell will also exit the terminal. An alternative way to use fish as a default interactive shell is to configure your terminal to run fish at startup, which is usually done with `-e` option. For example:
```
urxvt -e fish
```

## Sourcing bash scripts in fish

Install fisher package (function) manager for fish:
```
curl https://git.io/fisher --create-dirs -sLo ~/.config/fish/functions/fisher.fish
```

Add bass plugin:
```
fisher add edc/bass
```

Now you can source bash scripts within fish with:
```
bass source bash-script.sh
```

For simple use cases a simple alternative might also work:
```
exec bash -c "source some-bash-setup.sh; exec fish"
```

## Shell keyboard shortcuts

Shell keyboard shortcuts (might be some overlap with bash shell).

Cut the line from the cursor to the beginning of the line: `Ctrl+u`
Cut the line from the cursor to the end of the line; `Ctrl+k`
Paste the last thing you had copied: `Ctrl+y`

Delete a word after the cursor: `Alt+d`
Delete the last word of the line: `Ctrl w`

Go to the beginning of the line: `Ctrl+a` or `Home`
Go to the end of the line: `Ctrl+e` or `End`

Clear the screen while leaving the current line: `Ctrl+l`

Bash specific:
Edit the current command in your text editor: `Ctrl-x-e`

## Autosuggestions

Fish offers autosuggestions while you type.
To accept the whole suggestion: `[left arrow]` or `Control f`
To accept one word of the suggestion: `Alt f`

## Installing fish shell on systems without root access

An example from (probably needs to be updated):
<https://gist.github.com/masih/10277869>

```
#!/bin/bash
 
# Script for installing Fish Shell on systems without root access.
# Fish Shell will be installed in $HOME/local/bin.
# It's assumed that wget and a C/C++ compiler are installed.
 
# exit on error
set -e
 
FISH_SHELL_VERSION=2.1.1
 
# create our directories
mkdir -p $HOME/local $HOME/fish_shell_tmp
cd $HOME/fish_shell_tmp
 
# download source files for Fish Shell
wget http://fishshell.com/files/${FISH_SHELL_VERSION}/fish-${FISH_SHELL_VERSION}.tar.gz
 
# extract files, configure, and compile

tar xvzf fish-${FISH_SHELL_VERSION}.tar.gz
cd fish-${FISH_SHELL_VERSION}
./configure --prefix=$HOME/local --disable-shared
make
make install
```

So basically you download a source and configure it with autoconf to install fish in your local directory with `--prefix` option. 

## Aliases in Fish shell

Add aliases in your fish config `~/.config/fish/config.fish`:
```
alias vifm 'vifmrun'
```

## Fish one liners

Unzip all exported WhatsApp chats and change the name of the text files to the name of the group:
```
for f in *.zip; set -l name (echo "$f" | sed 's|\.zip|_chat\.txt|' | sed 's|WhatsApp\ Chat\ \-\ ||' | sed 's|\ |\_|' | tr -cd "[:print:]") ; unzip "$f" ; mv "_chat.txt" "$name" ; end
```

## fish history

You can retrieve all fish history with the `history` command:
```
history
```

Or just some entries with:
```
history --contains "search string"
```

You can use the same command to delete entries from history:
```
history delete --contains "search string"
```

You can also delete entries manually by editing file `~/.local/share/fish/fish_history`.

## atuin history search

You can use atuin for syncing, backing up and searching your shell history:
<https://atuin.sh/>

Install it through Pacman:
```
sudo pacman -Syu atuin
```

Add following in your fish config in `~/.config/fish/fish.config`:
```
atuin init fish --disable-up-arrow | source
```

I disabled the up arrow key bindings, so there is only `Ctrl-r` - you use it to search through your shell history.

