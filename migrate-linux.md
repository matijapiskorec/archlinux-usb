# Migrate Arch Linux installation to another disk

We will do a [Top to Bottom](https://wiki.archlinux.org/index.php/migrate_installation_to_new_hardware) approach where we will clone the root partition of our host system to the new system, then modify configuration files where needed. 

First, install rsync for advanced copying:
```
sudo pacman -S rsync
```

Useful links:
[Migrate installation to new hardware](https://wiki.archlinux.org/index.php/migrate_installation_to_new_hardware)
[Copy running Linux system to other machine over network](https://softwarebakery.com/copy-linux-systems-over-network)
[Clone a Linux install to another computer](http://positon.org/clone-a-linux-system-install-to-another-computer)
[Arch Wiki rsync Full system backup](https://wiki.archlinux.org/index.php/rsync#Full_system_backup)