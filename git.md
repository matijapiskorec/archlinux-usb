# Git versioning system

Install git versioning system:
```
sudo pacman -Syu git
```

## Basic git commands

Clone a repository:
```
git clone [REPOSITORY URL]
```

If you want just a specific file from Github, without the whole git repository, you can simply download the raw file directly. Find the link to the file's raw content and use wget:
```
wget [GITHUB RAW CONTENT LINK]
```

Check which files are modified:
```
git status
```

Add changes to staging area:
```
git add [file]
```

Commit changes:
```
git commit -m "Commit message"
```

Reset the last commit. Commit will be deleted and the changes will re-enter the staging area:
```
git reset HEAD~1
```

If you want to rename a file you should use a `git mv` command:
```
git mv [OLD FILENAME] [NEW FILENAME]
```

## Git configuration

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

In order to push to Github using ssh key, without having to type username or password, you have to setup origin of a repository. Go to the respository and check origin url:
```
git remote show origin
```

The origin url probably starts with `https://`, you have to change this to `git@` in order to authorize with ssh key. Change origin in the following way:
```
git remote set-url origin git@github.com:[USERNAME]/[REPOSITORY].git
```

Before you actually try to connect you have to add your ssh key to keychain:
```
keychain github_rsa
```

You can now check origin again with `git remote show origin`. If authorization succeeds without errors this means that your key works.


## Managing dotfiles with git bare repositories

Create a git bare repository where you will store your dotfiles:
```
git init --bare $HOME/dev/repo/dotfiles
```

Put the following in your `.bashrc` (if you are using bash) or `config.fish` (if you are using fish):
```
alias dotfiles='/usr/bin/git --git-dir=$HOME/dev/repo/dotfiles --work-tree=$HOME'
```

Run new shell to activate the alias. Configure your new bare repository not to show untracked files in order to ignore all of the non-dotfile files in your home directory:
```
dotfiles config --local status.showUntrackedFiles no
```

To add a file to your dotfiles repo just do:
```
dotfiles add .bashrc
```

You can check the current status:
```
dotfiles status
```

Commit and all other commands work the same as in normal git:
```
dotfiles commit -m "Commit message"
```

If you want to push it to Github, first create a repository named dotfiles on your Github account, then add the remote origin and push the changes from your local repo:
```
dotfiles remote add origin [PATH TO YOUR GITHUB DOTFILES REPO]
dotfiles push origin master
```

If you have a ssh authorization on your Github account then setup the remote url in this way:
```
dotfiles remote set-url origin git@github.com:[USERNAME]/[REPOSITORY].git
```

If you want to download all of your dotfiles just do (assuming you don't yet have dotfile aliases properly configured on your current system):
```
git clone --bare git@[PATH TO YOUR GITHUB DOTFILES REPO]
```
