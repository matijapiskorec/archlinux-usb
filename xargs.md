# Handling multiple arguments in command line with xargs

## Openning multiple files

Open all files containing "i3" from a current folder for editing in Sublime Text:
```
find . -name "*i3*" -print0 | xargs -0 subl
```

Open multiple files found by find command in vim tabs:
```
find [PATH] -name *keyword* -print0 | xargs -0 vim -p
```

## grep on multiple files

Use xargs to pass multiple files to grep and search for a string in all of them:
```
find [PATH] -name "*.txt" -print0 | xargs -0 grep "likelihood"
```

xargs delimits results on whitespaces by default, which is problematic if you work with filenames. You can force xargs to delimite find results with NULL and tell xargs to expect NULL as delimiter

## Word count for multiple files

Recursively find all Python files and count the number of lines:
```
find . -name '*.py' | xargs wc -l
```

If some filenames contain newlines this is the safe version:
```
find . -name '*.py' -print0 | xargs -0 wc -l
```

## Interactive search

Allow user to type a keyword which will be searched in all filenames in certain paths and outputed to terminal, after which user can type some other keyword:
```
xargs -L 1 find [PATH] -name
*Keyword*.md
```

To signal the end of input to xargs type `Ctrl d`.

## Unzip multiple archives

You can use find and xargs to unzip large number of zip archives:
```
find ~/path/ -type f -name "*.zip" -print0 | xargs -0 -n 1 unzip
```

Option `-n 1` is needed because otherwise xargs will try to feed one unzip command with multiple arguments, while we want at most one argument - one for each filename in the input. Additionally, you can unzip everything to standard output and search through all the lines with fzf (option `-e` is for exact matches):
```
find ~/path/ -type f -name "*.zip" -print0 | xargs -0 -n 1 unzip -p | fzf -e
```

## More complex commands

If using more complex commands it is useful to use replace string option `-I` which defines a string which will be replaced with the input to xargs (in this case the string is `{}` and it will be replaced with the file name provided by find command):
```
find ~/path/ -type f -name "*.pdf" -print0 | xargs -0 -I {} pdftotext "{}" - 2>/dev/null
```

For some reasone the above command works without `-n 1` although pdftotext does not work if you provide more than one file name! The `2>/dev/null` is to discard standard error because we don't want it in our final stream.

