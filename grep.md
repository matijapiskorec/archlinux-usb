List all lines containing `http` in all files in current folder and all subfolders (`-r`). Show relative line number (`-n`) and color output for easier reading (`--color=always`). Pipe resulst in color mode (`-R`):

```
grep --color=always -nr "http" . | less -R
```
