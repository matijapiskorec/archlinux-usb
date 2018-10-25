# Initial setup when starting Arch Linux Live USB

Load Croatian keyboard layout, update Pacman, install tmux and clone a git repository with instructions for installation:
```
loadkeys croat
pacman -Sy
pacman -S git
pacman -S tmux
git clone https://github.com/matijapiskorec/archlinux-usb
```