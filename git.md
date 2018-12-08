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

## Connect to Github using a public key

Generate key pair that you will use for authentification (when prompted for a password, you can use the one you usually use for Github for example):
```
ssh-keygen -t rsa ~/.ssh/github_rsa
```

Copy the generated public key to clipboard, for example with xclip:
```
xclip -sel clip < ~/.ssh/github_rsa.pub
```

Login to your Github account, go to `Settings`, then to `SSH and GPG keys`, and choose the option `Add SSH key`. Paste there your key.

To test the key, first add it to you key manager. I use keychain:
```
keychain github_rsa
```

You will have to do this every time you reboot. But once you add the key and type in the passphrase you won't have to do it again during the session.

Test your ssh connection to Github:
```
ssh -T git@github.com
```

If everything is ok and Github responds with your username, your key is set and you should be able to push without typing your password. You can check whether your key is added to the ssh-agent with:
```
ssh-add -L
```
