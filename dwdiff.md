# Finding differences in text files on a word level with dwdiff

Install dwdiff from Arch repository:
```
sudo pacman -Syu dwdiff
```

Now you can diff two text files on a word level. For my shell I define custom colors:
```
dwdiff -P --color=red,blue file1.txt file2.txt
```

I set an alias for these options in my Fish config `.config/fish/config.fish`:
```
alias dwdiff 'dwdiff -P --color=red,blue'
```

You can pipe the output of the command to `less -R`.

