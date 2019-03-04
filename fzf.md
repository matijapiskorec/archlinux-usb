# Fuzzy finder for command line

Install [fzf](https://github.com/junegunn/fzf) (fuzzy finder):
```
sudo pacman -Syu fzf
```

It works in both bash and fish shells. It receives from standard input a list of lines, allows fuzzy search on them and outputs the selected line. Similar to dmenu but on a command line.

Search through files in a specific directory, then open the chosen file in Sublime text editor:
```
find doc/note/evernote/* -type f -printf "'%p\n'" | fzf | xargs -r subl
```
