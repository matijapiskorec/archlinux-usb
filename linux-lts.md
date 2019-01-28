# Install Arch Linux LTS kernel

Check your kernel version with `uname -r`. You probably have standard Arch Linux kernel which updates frequently and has the newest features. If you want a more stable kernel which does not support newest hardware you can install Arch Linux long term support (LTS) kernel and update GRUB configuration:
```
sudo pacman -Syu linux-lts
sudo grub-mkconfig -o /boot/grub/grub.cfg
```

You can now reboot and check whether LTS kernel is offered in `Advanced options for Arch Linux` GRUB menu. If everything works fine you can remove the latest kernel with pacman and rebuild the GRUB config so that only LTS kernel is listed:
```
sudo pacman -R linux
sudo grub-mkconfig -o /boot/grub/grub.cfg
``` 

