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