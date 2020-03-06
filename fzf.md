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

## fzf display options

By default fzf occupies all of the terminal window. Sometimes it's more readable to restrict the height and reverse the output (so that the menu appears bellow the current line, not above). Also, fuzzy matching is sometimes unreasonable and it makes more sense to have exact matching:
```
cat file.txt | fzf --height 40% --reverse --exact
```

## fzf to search through unzipped files

You can use find, xargs, unzip and fzf to unzip large number of zip archives to standard output then search through all of the lines with fzf (option `-e` is for exact matches):
```
find ~/path/ -type f -name "*.zip" -print0 | xargs -0 -n 1 unzip -p | fzf -e
```

## Cool fzf options

Enable multiple selections in fzf with Tab: `-m`

