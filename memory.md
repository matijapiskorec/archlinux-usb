# Check installed RAM modules

Install dmidecode and lshw:
```
sudo pacman -Syu dmidecode lshw
```

Check installed RAM modules with:
```
dmidecode -t 16
lshw -class memory
```
