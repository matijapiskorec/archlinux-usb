# List open files with lsof

Install lsof program:
```
sudo pacman -Syu lsof
```

## Check files open by a specific program

Find process id for a specific program:
```
ps aux | grep vim
```

Check which files are oppened by this program:
```
lsof -p [PROCESS ID]
```

Where is the binary for a specific program:
```
lsof -p [PROCESS ID] | grep bin
```

Which shared libraries did the program open:
```
lsof -p [PROCESS ID] | grep \.so
```

Which programs are listening on specific ports (80 in this case):
```
lsof -i :80
```

# Check files open by specific user

Check files open by a specific user:
```
lsof -u [USER]
```

