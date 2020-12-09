# Memory management in Arch Linux

## Check installed RAM modules

Install dmidecode and lshw:
```
sudo pacman -Syu dmidecode lshw
```

Check installed RAM modules with:
```
sudo dmidecode -t 16
sudo lshw -class memory
```

## Check memory usage of all programs with htop

To check memory usage of all programs run htop:
```
htop
```

Shortcuts:

Search for a process with specific name: `F4`
Send a kill signal to process: `F9` (press it twice and then Enter)
Quit htop: `q`

## Check memory usage of a program with pmap

Check a memory usage of a process with process ID 6606 (you can list multiple ID's as well):
```
sudo pmap 6606
```

To extract only total memory usage which is printed at the end:
```
sudo pmap 6606 | tail -n 1
```

## Create swap file

Create 8GB swap file (the same size as your RAM):
```
fallocate -l 8G /swapfile
```

Change its access rules, format and enable it:
```
chmod 600 /swapfile
mkswap /swapfile
swapon /swapfile
```

Also, add this Swap file to the /etc/fstab:
```
echo '/swapfile none swap sw 0 0' >> /etc/fstab
```

## Resize swap file

How to Increase Swap Size in Ubuntu Linux
<https://linuxhandbook.com/increase-swap-ubuntu/>

I'll do this to increase my swap file form 8 GB to 16 GB - I need this to compile python-graph-tool from AUR, which otherwise fills my 8 GB RAM and 8 GB swap file!

