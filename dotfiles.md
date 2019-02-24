# Managing dotfiles with git bare repositories

managing all your dotfiles can be tedious. Keep them in a bare git repository from where you can easily retrieve them when installing the new system. First, create a bare dotfile repository:
```
git init --bare $HOME/dotfiles
```

Add this alias to the `.bashrc`:
```
alias config='/usr/bin/git --git-dir=$HOME/dotfiles/ --work-tree=$HOME'
```

Run some basic configuration in terminal:
```
config config --local status.showUntrackedFiles no
```

Basic usage example:
```
config add /path/to/dotfile
config commit -m "Short message"
config push
```
