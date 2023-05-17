# Foremost tool for recovery of deleted files

Install foremost:
```
sudo pacman -Syu foremost
```

Run the recovery for USB drive. This should work but it doesn't:
```
foremost -v -q -t tex -o tmp/download/recover -i /dev/sdb3
```

This works:
```
foremost /dev/sdb3 -v -o /home/matija/tmp/download/recover/
```

