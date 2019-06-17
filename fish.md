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

Go to the beginning of the line: `Ctrl+a` or `Home`
Go to the end of the line: `Ctrl+e` or `End`

Clear the screen while leaving the current line: `Ctrl+l`

Bash specific:

Edit the current command in your text editor: `Ctrl-x-e`

