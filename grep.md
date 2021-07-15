# Grep

List all lines containing `http` in all files in current folder and all subfolders (`-r`). Show relative line number (`-n`) and color output for easier reading (`--color=always`). Pipe results in color mode (`-R`):

```
grep --color=always -nr "http" . | less -R
```

List all lines not containing string ",0" from file.txt:
```
grep -v ',0' file.txt 
```

