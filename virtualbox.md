# VirtualBox

You have to install following packages (this is for my Linux LTS kernel):

    sudo pacman -Syu virtualbox linux-lts-headers virtualbox-host-dkms

For standard kernel you would install:

    sudo pacman -Syu virtualbox linux-headers virtualbox-host-modules-arch

Make sure you are not doing partial install and update (`pacman -Sy`) because then the kernel and the headers might not match!

Bad...

    > pacman -Q linux-lts-headers linux-lts
    linux-lts-headers 6.6.34-1
    linux-lts 6.6.31-1

Good...

    > pacman -Q linux-lts-headers linux-lts
    linux-lts-headers 6.6.34-1
    linux-lts 6.6.34-1

Make sure to update your system with pacman `pacman -Syu` or else you migt end up with partial update!
<https://wiki.archlinux.org/title/VirtualBox#Load_the_VirtualBox_kernel_modules>

You probably also need to run kernel module manually - this one is required to run any VirtuaBox virtual machine:

    sudo modprobe vboxdrv

Also, make sure you enable Intel Virtualization Technology in your BIOS!
