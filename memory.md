# Check installed RAM modules

Install dmidecode and lshw:
```
sudo pacman -Syu dmidecode lshw
```

Check installed RAM modules with:
```
sudo dmidecode -t 16
sudo lshw -class memory
```
