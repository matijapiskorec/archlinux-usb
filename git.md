# Git versioning system

Git log in pretty format:
```
git log --graph --pretty=format:"%Cred%h%Creset -%C(yellow)%d%Creset %s %Cgreen(%cr) %C(bold blue)<%an>%Creset" --abbrev-commit
```

Make an alias command for this:
```
git config --global alias.hist 'log --color --graph --pretty=format:"%Cred%h%Creset -%C(yellow)%d%Creset %s %Cgreen(%cr) %C(bold blue)<%an>%Creset" --abbrev-commit'
```

Now run a command with:
```
git hist
```

You can also add following line to your global `~/.gitconfig` (this is another example of log formatting):
```
alias.hist=log --pretty=format:"%h %ad | %s%d [%an]" --graph --date=short
```

If you want to see which lines changed:
```
git hist -p
```

Setup global user name and email:
```
git config --global user.name "Matija Piskorec"
git config --global user.email "matija.piskorec@gmail.com"
```

Check your git configuration for all levels (system - for all users, global - for you, repository - for this repository):
```
git config --list | cat -n
```

You can pipe any of the settings to external file (for example another git configuration):
```
git config --list | sed -n 24p >> git.txt
```

Use silent less (without beep sound) when running git diff and similar paging commands:
```
git config --global core.pager 'less -q'
```
