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

## The only cheat sheet you need

Unified access to the best community driven documentation repositories in the world [https://cheat.sh/](https://cheat.sh/), and on [Github](https://github.com/chubin/cheat.sh).

From the browser: [https://cheat.sh/python/lambda](https://cheat.sh/python/lambda)

From the command line:
```
curl cht.sh/python/lambda
```

From the same author (Igor Chubin), more fun with `curl` and a [list of awesome console services](https://github.com/chubin/awesome-console-services).

For example, fetch teh weather forecast in terminal:
```
curl wttr.in
```

Or exchange rates for cryptocurrenices:
```
curl BTG.rate.sx
curl rate.sx/btc
curl rate.sx
curl rate.sx/eth@30d  # Ethereum to USD rate for the last 30 days
curl eur.rate.sx/btc@february  # How Bitcoin (BTC) price in EUR changed in February
```

## Symlinks

To create a symlink to a directory or file, use:
```
ln -s /absolute/path/to/directory /absolute/path/to/symlink
```

In case symlink already exists (maybe in a broken state) you can force the link creation with the `-f` option.

Most commands see symlinks as actual files. If it is a directory, you can `cd` to it. If it is a file, you can open and change it. If you delete an actual link only the link is deleted, not the actual file.

To copy dereference symlinks as actual files use `-L` option in cp and rsync:
```
cp -rL /absolute/path/to/symlink /absolute/path/to/directory
rsync -aAXvL /absolute/path/to/symlink /absolute/path/to/directory
```

## Batch rename files

For batch renaming files, use rename utility from util-linux. For example, to rename files `file***.jpg` to `FILE***.jpg` for all jpg files in the current folder use:
```
rename file FILE *.jpg
```

## Measuring execution time of commands

Bash has a built-in time command, which is not available in fish shell. Instead, you can install and use time command from pacman repository:
```
sudo pacman -Syu time
```

Now you can time any command by simply prefacing it with `time`:
```
time ls
```

## Unique lines

Count unique lines in a stream: `cat file.txt | uniq -c`

## choose - a simpler alternative to awk and cut

choose is a command line utility which functions as a simpler alternative to cut and awk. Install it through AUR:
```
git clone https://aur.archlinux.org/choose-rust-git.git
cd choose-rust-git
makepkg -sri
```

Now you can pipe into choose to select columns from text stream. For example to print 5th item from a line: `choose 5`

For more info see Github Readme:
<https://github.com/theryangeary/choose>

## Find file with file name

To find a file with file name recursivelly within home directory:
```
find /home/matija -iname "*Mathematical Principles*"
```

## Watching the commands with watch

If your command gives a static output and you need to run it avery now and then, you can use the watch command to automatically run it multiple times. For example, memory consumption:
```
watch free -m
```

You can use any command and its parameters, the only restriction is that you cannot use aliases! This is because watch is shell-agnostic - it does not have access to shell aliases.

Some useful watch use cases:
```
watch df -h
watch tail ~/tmp/log/[LOG FILE]
```

## Sorting in command line

Sort first by the third, then by the second column, where columns are comma-delimited (as opposed to default space-delimited):
```
sort -t, -k3 -k2 [FILE]
```

Sort by the first column, considering that the first column is a numeric value (otherwise the sort will be lexicographic, so for example `11` would sort lower than `2`):
```
sort -t, -n -k1 [FILE]
```

## Searching with ripgrep

ripgrep is a great and fast replacement for grep, you can install it:
```
sudo pacman -Syu ripgrep
```

And use the binary rg for searching within all files in a directory:
```
rg keyword ~/doc/note/evernote
```

Unline grep, you can also use it for search and replace, if you don't want to use sed or awk for that. More info here:
<https://hackaday.com/2020/10/14/linux-fu-global-search-and-replace-with-ripgrep/>

Of course, for more options consult the man documentation:
```
man rg
```

## Named pipes

You can create a named pipe which acts like a regular file which can be piped into or out of:
```
mkfifo /tmp/pipe
```

You can now pipe into it like it is a regular file:
```
ls > /tmp/pipe
```

And pipe out of it:
```
cat /tmp/pipe
```

Or pipe its contents into another command:
```
fzf < /tmp/pipe
```

You can also delete it like a regular file (although here it is on `/tmp` which is mounted in memory, and besides, it does not actually store any data but only redirects outputs between processes):
```
rm /tmp/pipe
```

Named pipes reside completelly in memory and there is no data transfer unless both ends of the pipe are open. Here is another interesting example. Create a named pipe and listen what is piped into it:
```
mkfifo /tmp/pipe
tail -f /tmp/pipe
```

Now push some messages through in another terminal:
```
echo "This is a message!" > /tmp/pipe
```

## Conversion from UNIX epoch date

Convert the timestamp in UNIX epoch time to human-readable format:

    date -d @1590507378
    Tue May 26 05:36:18 PM CEST 2020

## Reverse the output

Reverse the output with `tac`
```
ls -la | tac
```

## Redirecting standard output and error

Bash – Redirect both standard output and standard error to same file
<https://linuxconfig.org/bash-redirect-both-standard-output-and-standard-error-to-same-file>

Redirect standard output to a file (overwrite) and standard error to terminal:
```
echo "linuxconfig.org" > new-file.txt
```

Redirect standard output to a file (append) and standard error to terminal:
```
echo "linuxconfig.org" >> existing-file.txt
```

Redirect standard output and standard error to the same file:
```
echo "linuxconfig.org" > new-file.txt 2>&1
```

Supress standard output and standard error by redirecting them to `/dec/null`:
```
echo "linuxconfig.org" > /dev/null 2>&1
```

Redirect standard output to one file and standard error to another file:
```
echo "linuxconfig.org" 2> std-err.txt 1> std-out.txt
```

Redirect standard output and standard error to the same file while also seeing them both in your terminal:
```
echo "linuxconfig.org" 2>&1 | tee new-file.txt
```

Redirect standard output and standard error to the same file (append) while also seeing them both in your terminal:
```
echo "linuxconfig.org" 2>&1 | tee -a existing-file.txt
```

## Checking last login users

Check the last login of users with the `lastlog`
Show a listing of last logged in users `last`

## Fetch multiple files with wget

To fetch multiple files using their URL's with wget you can simply do:
```
wget URL1 URL2 URL3
```

