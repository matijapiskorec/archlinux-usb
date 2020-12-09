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

Clone into a specific folder:
```
git clone [REPOSITORY URL] [FOLDER NAME]
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

Revert unstaged changes in the current directory (omit the dot at the end to check just what will be changed):
```
git checkout -- .
```

Revert both staged and unstaged changes in the current directory:
```
git reset --hard HEAD
```

To discard unstaged changes on a specific file:
```
git restore [FILE]
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

## Github Pages

Github Pages is a great hosting service for static web pages. If you already have a static webpage which you would like to host, this is how you do it.

First, go to your Github account and create an empty repository (assumption is that your username is `username` and repository name is `repository-name`). Then go to your filesystem, in the folder where your webpage is, and initialize a git repository which you will connect to the one on Github:
```
git init
git add .
```

This will add all files withing your folder. At the bearest minimum you should have a README.md file, or if you actually want a webpage to host, an index.html file. If there are any files which you want to remove from staging area use:
```
git rm --cached file.txt 
```

Now you can commit the changes to your local repository:
```
git commit -m "Initial commit"
```

Recently Github introduced a requirement to rename the master branch to main, and the main branch now becomes default for a repository. You can rename your master branch with this command:
```
git branch -M main
```

If you have a public key set up on your account:
```
git remote add origin git@github.com:username/repository-name.git
```

Or a normal login with username and password:
```
git remote add origin https://github.com/username/repository-name.git
```

You can now push the changes to the remote repository on Github:
```
git push -u origin master
```

Or, if you renamed your master branch to main:
```
git push -u origin main
```

Now go to your repository Settings under Github Pages section and select your master branch as the source. Now you master branch is served as a static webpage and you can access it line in your browser by following this link:
<https://username.github.io/repository-name/>

## Github stash

To make a quick stash which stashes all staged and unstaged changes to all files (but not untracked and ignored files!):
```
git stash
```

Stash all current changes, both staged and unstaged, in a stash with description:
```
git stash push -m "Message"
```

Include all untracked files: `-u`, `--include-untracked`
Include all untracked files as well as ignored files: `-a`, `-all`

You can also provide a list of files to stash as the last argument (I'm not sure whether options `-u` and `-a` make sense in this case?).

Reapply previously stashed changes and remove them from the stash:
```
git stash pop
```

Reapply previously stashed changes and leave them in the stash:
```
git stash apply
```

List all stashes:
```
git stash list
```

Pop or apply a specific stash from the list:
```
git stash pop stash@{0}
```

Show the list of changes in the last stash (apparently the untracked files are not shown, although they are in the hash as well!):
```
git stash show
```

Show exact changes in the last stash:
```
git stash show -p
```

Drop a stash entry:
```
git stash drop
```

Drop all stashes:
```
git stash clear
```

Note: Some tutorials refer to the `git stash save` command. The save command is depracated in favor of push, so just use push!

