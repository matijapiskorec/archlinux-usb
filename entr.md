# Running programs automatically upon file update with entr

entr is a program that runs arbitrary scripts and programs whenever any of the tracked files changes. It is available in Arch repository:
```
sudo pacman -Syu entr
```

You supply filenames to track via standard input. For example, you can track all tex and bib files in root directory as we as all files in figures folder, and run make command whenever any of them changes:
```
ls *.tex *.bib figures/* | entr make
```

Unfortunatelly, deleting some of the existing files will crash entr, and adding new files will not trigger the make command as entr does not track them.

## Run entr from background

Run entr from background:
```
(echo log1.txt | entr -rp cat log1.txt > log2.txt &)
```

The same example but with running LaTeX autocompile:
```
(ls *.tex *.bib figures/* | entr -rp make &)
```

This command is not in the jobs queue, you have to manually find a process id with `ps aux | grep entr` and kill it with `kill -9 [PID]`.
