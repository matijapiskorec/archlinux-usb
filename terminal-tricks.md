# Terminal tricks

List file with line numbers:
```
less -N .bashrc
cat -n .bashrc
```

Append lines 14-16 from .bashrc to another file:
```
sed -n 14,16p .bashrc >> i3-setup.txt
```

Execute line 5 from .bashrc file:
```
$(sed -n 5p .bashrc)
```

Clone a html guide from Github and convert it to text for easy reading:
```
sudo pacman -S w3m
git clone https://gitlab.com/c.magyar/archlinux-usb.git
w3m -dump archlinux-usb/html/arch-usb.html | less
```

Open all files starting with "i3" from a current folder for editing in Sublime Text:
```
ls | grep i3 | xargs subl
```

Pipe to clipboard using xclip. First, install xclip:
```
sudo pacman -S xclip
```

Pipe results of ls command onto clipboard:
```
ls -la | xclip -selection clipboard
```

Or git log command (clip also works instead of clipboard):
```
git log | xclip -selection clip
```

Default X selection that xclip uses is primary (can be pasted inside terminal), there is also secondary (not sure where this is used) and clipboard (can be pasted inside other applications, not terminal). 

# Share bash history between terminals

In order to share bash history between terminals, put the following two lines in `.bashrc`: 
```
shopt -s histappend
export PROMPT_COMMAND="${PROMPT_COMMAND:+$PROMPT_COMMAND$'\n'}history -a; history -c; history -r"
```

First command makes sure to append to the history file instead of overwriting it. Second command makes sure that bash appends to the history file and rereads it after every command.
