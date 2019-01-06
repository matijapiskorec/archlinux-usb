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

## Clipboard management

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

## Process the command history list

Process the command history list with fc. If you misstyped a command you can just run fc:
```
fc
```

And it will open the last command in the editor defined in the EDITOR environment variable (vi by default). You can then modify the command, save and exit to make it execute. If you want to set micro as the default editor instead of vi put the `export EDITOR=micro` in your `.profile` (for system-wide settings which is used by programs such as sudoedit and git) and `.bashrc` (just for bash sessions).

List last 5 lines of history:
```
fc -l -5
```

## Share bash history between terminals

In order to share bash history between terminals, put the following two lines in `.bashrc`: 
```
shopt -s histappend
export PROMPT_COMMAND="${PROMPT_COMMAND:+$PROMPT_COMMAND$'\n'}history -a; history -c; history -r"
```

First command makes sure to append to the history file instead of overwriting it. Second command makes sure that bash appends to the history file and rereads it after every command.

## Create multiple folders

Create `paper` with folders `figures` and `data` already inside:
```
mkdir -p paper/{figures,data}
``` 

You can nest folder hierarchy as deep as you want. Lets make two subfolders `pdf` and `jpg` inside `figures`:
```
mkdir -p paper/{figures/{pdf,jpg},data}
```

Lets use the same herarchy but make 5 folders inside `data` that all begin with `tmp` and are indexed with numbers:
```
mkdir -p paper/{figures,data/tmp{1..5}}
```

Folders could also be created recursivelly. Create `figures` and `data` and within each of them create `trash` and `backup` folders:
```
mkdir -p paper/{figures,data}/{trash,backup}
```

## Log inputs and outputs from piped commands

If you want to intercept outputs from a pipe, for example to log it into a file, you can use tee command. It will read standard input and redirect it to one or several files, as well as to standard output so that the pipe is not interrupted. Here it intercepts and logs an echo command which is heading to `/dev/null`:
```
echo 'Text being piped to null' | tee -a log.txt | cat > /dev/null
```

## Managing processes

Run a command in background:
```
[COMMAND] &
```

You can check current processes with jobs command:
```
jobs
```

Bring the job from background to foreground:
```
fg %[ID FROM JOBS COMMAND]
```

If you run a command and don't want to wait for it to finish, you can send it the suspend signal `Ctrl+Z`. It will be stopped, and you can run it in background by running:
```
bg %[ID FROM JOBS COMMAND]
```

For both fg and bg, if there is no id supplied, the most recent job will be put respectively to foreground or background.

The running jobs will not be available on another terminals. But you can still send them signals with kill command. First, find the process id (pid):
```
ps aux | grep [COMMAND OR SOME IDENTIFIER]
```

Check all possible signals with:
```
kill -l
```

Suspend a process:
```
kill -20 [PID]
```

Continue a process:
```
kill -18 [PID]
```

Terminate a signal (soft kill, process has a chance to cleanup):
```
kill -15 [PID]
```

Kill a signal (hard kill, process is killed by a kernel):
```
kill -9 [PID]
```

If you have a long running process and you want to exit the terminal, you can disown the process and it will continue to run in background even after the parent process (bash session) ended:
```
disown -a && exit
```

This will actually disown all running processes in this bash session. There is nothing you can do after except let the finish or send the signals, you cannot attach a new bash session to them again. Actually, you can try with reptyr program, although I did not manage to make it work (kernel complained):
```
sudo pacman -Syu reptyr
reptyr [PID]
```
