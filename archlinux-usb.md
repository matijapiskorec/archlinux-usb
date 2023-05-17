# Persistent Bootable ArchLinux USB by C.Magyar

## Overview

This page explains how to install Arch Linux on a USB key (flash drive). The end result will be a persistent installation identical to that on a normal hard drive with the goal of maximum compatibility with any machine the flash drive is boot on.

## Why Arch Linux?

There are already several guides to setting up a persistent Linux installation on a USB drive out there, including a decent ArchWiki page. In theory, an installation on a USB key should be no different than any other installation, and perhaps some GUI installers out there will work just fine. However I've heard of several failed attempts at getting a USB Linux installation working properly when working from said installers or guides. I have a few ideas on why this might be occurring and have attempted to correct these scenarios with this process. Arch Linux serves this purpose well due to its ability to easily change configuration options to the user's need.

## About this guide

Perhaps the biggest reason for the existence of this entire guide is my own curiosity. You may find the nature of an Arch Linux installation provides more insight into what is happening behind the scenes than any GUI installation tool out there. Messing around with Linux like this can be fun (and frustrating!). I find learning how my computer works and finely tuning its configuration to be rewarding. With an Arch Linux persistent bootable USB I have my own completely custom operating system, application set, and user interface with me in my pocket everywhere I go!

Also, I suppose I should say, I am in no way officially associated with Linux or the Arch Linux project. I am simply a curious tinkerer who uses the act writing things like this as a learning experience. I have personally followed these steps over a dozen times on multiple computers with no problems, but I can't guarantee it will work for you. I wrote this guide to be (hopefully) followable by anyone with a moderate understanding of current PCs. My intention is for this to be a fully self contained guide, yet numerous links are provided throughout the text to supporting references and additional resources.

## Before You Begin

To begin this installation you will need a USB flash drive to install on, of course. Although a typical Arch Linux installation with a fully functional desktop environment usually ranges from about 3GB to 5GB, I recommend using at least a 16GB stick. Being that this is an entirely portable Linux system of your own, you may want to load it up with a collection of some great GNU and open source software packages out there. With some large packages like SageMath , TeX Live, and various developer tools, my current Arch Linux USB drive sits at around 12GB.

## Live image

You will also need to download an Arch Linux bootable installation ISO and either burn it to a CD or write it to a different USB stick than the one you will be installing your persistent copy on. I have used both methods with no problems, but the speed of installation is much greater when using a bootable USB stick.

To write a bootable USB installation medium in Linux, run the following command; `/path/archlinux.iso` is the path to the downloaded ISO and `/dev/sdX` is the path to your unmounted target USB drive:
```
dd bs=4M if=/path/archlinux.iso of=/dev/sdX status=progress && sync
```

To make a bootable USB using Windows, I have used the open source GUI tool Rufus on several occasions without any issues. If Rufus doesn't work for you, there are multiple other programs intended for the same thing.

Users with a current working installation of Arch Linux can opt to forgo a new boot medium altogether and simply partition, format, pacstrap, and arch-chroot into the target USB drive instead. The instructions to do so are not explicitly provided here as that is not the scope of this guide, but the important parts of the process are identical.

## Wired vs wifi

For the actual installation you will need a computer connected to the internet. A wired connection is definitely preferred as the bootable installation ISO is setup to automatically detect and connect to any wired network on bootup. Also, any packages you choose to install will need to be downloaded from the Arch Linux repositories, and network speed may be a limiting factor over wifi.

The instructions in this guide will setup your persistent bootable USB to automatically configure a wired network connection whenever a network cable is detected. Support for most wifi interfaces will also be installed, but automatic connection will not be enabled. Having automatic wifi connection capability is quite simple to setup, but for this bootable Linux USB it won't be enabled by default as not every machine it is boot on will even have a wifi interface.

Lastly, Linux kind of has a horrible history of working with some wifi interfaces. There is a chance, albeit rare, that you may be the proud owner of a wifi networking device not compatible with Linux... yet (until you write the driver for it!). For more information pertaining to Linux wireless interface compatibility, see the official wireless wiki.

## BIOS vs UEFI

Basically, there are two different systems implemented today that motherboards use to communicate between an operating system and their firmware. There is the standard (legacy) BIOS (basic input/output system), and there is the newer UEFI (unified extensible firmware interface). Although UEFI was implemented on some top-end machines in the early 2000s, any computer more than six or seven years old is probably only going to be able to boot up in BIOS mode. Newer machines, on the other hand, will often be capable of booting in both UEFI mode and BIOS mode. Many times a preferred boot mode can be selected from the BIOS menu on such machines. Current Apple computers only recognize UEFI.

Both BIOS and UEFI require different particular partition schemes in order to boot. If the motherboard is set to boot in UEFI mode only and the inserted boot media does not have the correct partition scheme for UEFI, the boot will fail; the same goes for an attempted BIOS boot. This is one place I believe some of the USB installation guides out there fail: they often only describe how to create a USB boot device that uses only one mode. It is possible, however, to setup a USB drive that will have a partition scheme allowing it to boot in both modes and still use the same persistent installation of Linux. This guide will setup such a scheme in the partitioning and formatting sections below.

On most newer machines, you will be presented with the option to boot in either BIOS or UEFI mode from your bootable USB. This means the machine recognizes the UEFI boot media, but it does not always mean the machine is actually set to boot in UEFI mode, and selecting the UEFI boot option may fail. Selecting a mode that the motherboard is not set to boot in will not damage anything or touch any of the other drives on the machine, the boot will simply fail and one can reboot in the other mode. The USB stick created with this guide has been able to boot on every (about a dozen) desktop and laptop, new and old, BIOS and UEFI, machine that I have tried it on.

## Secure boot

The new UEFI specification also includes an optional mechanism to protect against pre-boot malware. The secure boot protocol is designed to only allow the booting of images signed with a cryptographic key contained in a machine's NVRAM. If secure boot is enabled and a boot image lacks a cryptographic signature or the signature doesn't correspond to a key listed in the computer's NVRAM, the firmware will refuse to execute the boot image. The most common workaround when dealing with secure boot on Linux machines is to simply disable the secure boot option in the machine's BIOS menu.

If you do not wish to disable secure boot or it is not possible to disable secure boot, you will need to properly sign the boot loader image with a Microsoft key. Due to the Microsoft requirement that all computers sold with a factory installed copy of Windows 8 ship with secure boot enabled, vendors have had to include Microsoft's keys in the NVRAM of all new computers. This means any boot image signed with a Microsoft key will properly execute on a machine with secure boot enabled.

Signing the boot loader image of the Arch Linux USB with a Microsoft key is entirely possible, but will not be explicitly covered in this guide. Personally, I have encountered few public machines with secure boot enabled, but in the name of ultimate utility, signing with a Microsoft key is recommended. For instructions on signing the Arch Linux USB with a Microsoft key, see the extra options.

## Localtime vs UTC

There are two time standards used by the internal hardware clock of a modern computer to store the current time. Localtime is dependent on the machine's current geographical time zone and often takes daylight savings into account, while UTC (coordinated universal time) is the same regardless of global location. The hardware clock stores the current time, in one of these two formats, by storing separate values for year, month, day, hour, minute, and  second.

The hardware clock does not, however, retain any record of what format its time values are kept in or if there has been any adjustment made for daylight savings. It's up to the operating system to keep track of these settings. This can pose some issues if multiple operating systems are boot on the same computer using localtime as its time format. For instance, both operating systems might adjust the hardware clock time for daylight savings resulting in an extra hour of difference.

The obvious solution, here, is to simply use UTC on all operating systems and be done with it. MacOS uses UTC, Linux uses UTC by default, but Windows uses localtime by default. In other words, when booting the Linux USB off of a machine primarily used with Windows, the chances are that the hardware clock is going to appear to be incorrect.

What this means for the Linux USB is that you may occasionally see some time-stamp warning messages when you boot up your USB off different machines. We will enable a network time protocol so that the USB Linux system will update its operating system clock as soon as an internet connection is established and correct these discrepancies. More importantly, though, the Linux system will also update the hardware clock to the correct time in UTC, meaning the next time Windows is boot it may encounter some time-stamp errors. In my experience, this hasn't been an issue beyond the infrequent warning message at bootup.

## i686 vs x86_64

Arch Linux is optimized for both i686 (32-bit) and x86_64 (64-bit) machine architectures. While a single 32-bit installation will boot on both types of machine, it is not optimal for a 64-bit machine. The 32-bit version of Arch Linux can be installed from any machine, but to install the 64-bit version you must be booted on a 64-bit machine.

Besides that, the choice of a 32-bit versus a 64-bit installation of Arch Linux is entirely up to the you. Simply select the desired version from the initial installation ISO boot menu: Boot Arch Linux (x86_64) for a 64-bit installation, or Boot Arch Linux (i686) for a 32-bit installation.

It is possible to make make two separate installations (64 and 32-bit) on two different partitions of the same USB stick. This page only explicitly describes the process of setting up a single partition and installation of Arch Linux. For information on setting up multiple partitions with multiple persistent operating systems, see the extra options.

The personal Linux USB I've been using has a single 64-bit installation, and lack of compatibility has yet to be an issue.

## Partitioning notes

Another possibly useful option not explicitly shown in this guide is partitioning the target USB device to function as both a persistent bootable USB and an NTFS or FAT32 formatted storage device fully compatible as a Windows, Linux, or OSX standard USB jump drive. See the extra options.

A final thing to point out is the lack of a swap partition in this installation of Linux. The reason for this is twofold. First, recognizing that flash memory has a finite number of writes before it eventually goes bad, the lack of a swap partition may at least decrease some of those writes. Second, realizing that nearly any computer you boot up onthese days has at least a few gigabytes of available RAM, the need for a swap partition is mostly non-existent.

## Boot Up the Live Installation ISO

Insert you USB or CD installation medium in the computer and boot it up. Use the computer's boot menu (usually invoked with [F12] on a PC or the [option] key on a Mac) to select the inserted boot media. When presented with the boot device selection menu, select the entry for either BIOS or UEFI as explained above.

A bootloader menu will appear with several options. Select the Boot Arch Linux (x64_86) or (i686) option as explained above. After a minimal amount of necessary drivers are loaded to RAM, you will be presented with a root Z shell prompt.

## Keymap and/or language

The default console keymap and language in the live shell are, respectively, US and US English UTF-8. For my purposes (speaking mostly English, living mostly in Wisconsin) this has always been exactly what I needed, and the steps below to change these settings have never been required.

If a different keyboard mapping is required, view the available keymaps:
```
ls /usr/share/kbd/keymaps/**/*.map.gz | less
```

Load the required keymap. Here, mapname is the filename of the required map
without path or file extension:
```
loadkeys mapname
```

To change the language of the live root environment, edit `/etc/locale.gen` and uncomment the line containing your desired language (for US English, uncomment `en_US.UTF-8 UTF-8`):
```
nano /etc/locale.gen
```

Generate the locale information:
```
locale-gen
```

Ensure the LANG variable is set in `/etc/locale.conf`:
```
cat /etc/locale.conf
```

If it is incorrect or not present, create a new `/etc/locale.conf`; `localeline` is the first word of the uncommented line in `/etc/locale.gen` (for US English, this is `en_US.UTF-8`):
```
echo LANG=localeline> /etc/locale.conf
```

## Connect to the Internet

If there is an active networking cable plugged into the machine, the live shell will bring up the computer's network interface card and automatically attempt to lease an IP address from the network during bootup. To check the network connection, ping some website:
```
ping -c1 google.com
```

## Wired

If you have an active networking cable is plugged into the machine and you are unable to connect to the internet, begin troubleshooting by viewing the interface names and statuses:
```
ip link
```

Ensure the network device is powered; ethname is the name of the interface of type link/ether (most likely the name is `eno1` or `eno0`):
```
ip link set ethname up
```

Now attempt to manually lease a DHCP IP address from the network:
```
dhcpcd ethname
```

If you are issued a lease, try to ping an outside server again:
```
ping -c1 archlinux.org
```

If you still aren't connected or were unable to lease an IP address, view all the instances of dhcpcd to see what the hell is going on:
```
systemctl list-units | grep dhcpcd
```

See detailed instance information to troubleshoot any hardware issues:
```
systemctl status dhcpcd@ethname.service
```

If you still can't connect to the internet, see the ArchWiki for further help.

## Wireless

If a wired connection is unavailable or you prefer to use wifi, most wireless interfaces are supported by the drivers on the installation ISO. To check if this is possible on your current machine, see if any kernel drivers have been loaded for the wireless interface:
```
lspci -k | grep -A3 "Network controller"
```

If no device is present or no drivers have been loaded, you are mostly out of luck; although it technically may be possible to import the proper drivers via some other removable memory device, such a procedure is far beyond the scope of this guide. If you really want to keep pursuing this route, checkout the official Linux wireless wiki and the ArchWiki wireless page to get started.

If the drivers have been loaded, view the names of any available wireless interfaces:
```
iw dev
```

Now bring the wifi interface up. Here, wifiname is the wifi interface name given by iw dev (the name will generally be six characters long, most likely starting with wlp followed by three additional numbers and/or letters):
```
ip link set wifiname up
```

Scan for available networks:
```
iw dev wifiname scan | grep "SSID:"
```

If you don't know what type of authentication is required by the network you want to connect to, view the full scan results:
```
iw dev wifiname scan | less
```

For a connection with no encryption; networkname is the network you wish to connect to:
```
iw dev wifiname connect "networkname"
```

For a connection with WPA/WPA2 encryption (most likely scenario); password is the wifi password:
```
wpa_supplicant -i wifiname -c <(wpa_passphrase "networkname" "password")
```

For a connection using WEP (old, not likely):
```
iw dev wifiname connect "networkname" key 0:"password")
```

Once a connection is established, fork the process to the background by pressing `[ctrl]+z` and typing `bg`.

Finally, attempt lease an IP address:
```
dhcpcd wifiname
```

Check your network connection:
```
ping -c1 archlinux.org
```

If you are unable to obtain a wireless network connection, see the ArchWiki for more information (good luck!).

## System time

Once connected to the internet, turn on the network time protocol to synchronize system time:
```
timedatectl set-ntp true
```

## Prepare USB Stick

As mentioned earlier, this Arch Linux bootable USB stick will be compatible with both BIOS and UEFI booting modes. In order for a storage device to boot in BIOS mode, the first 512 bytes of the device's memory must contain an MBR (master boot record). For a storage device to boot in UEFI mode, a special ESP (EFI system partion) is required. Both partitions can be created using gdisk.

Before proceeding, determine the device name of the target USB drive. First, before plugging in the target USB, view the currently available block devices:
```
lsblk
```

Now insert the target flash drive and view the devices again. The newly detected device `/dev/sdX` is the name of the target USB you will use for further partitioning and formatting. Note that in the device name you will use is literally `/dev/sdX` where the only thing that changes is the single lowercase letter value of X. Double check that you have the correct device name `/dev/sdX`, lest you may repartition the internal hard drive of the machine you are on!

## Partition

There are several partitioning tools available in the live installation environment. We'll use gdisk to partition the target USB device:
```
gdisk /dev/sdX
```

First wipe the partitions on the target USB device by typing d at the interactive prompt until no partitions remain:
```
Command (? for help): d
No partitions
```

Then, make a 10MB MBR partition starting in the beginning of the device's memory:
```
Command (? for help): n
Partition number (1-128, default 1):
First sector (34-XXXXXX), default = 64) or {+-}size{KMGTP}:
Last sector (64-XXXXXX), default = XXXXXX) or {+-}size{KMGTP}: +10MB
Current type is 'Linux filesystem'
Hex code or GUID (L to show codes, Enter = 8300): EF02
```

Create a 500MB ESP partition:
```
Command (? for help): n
Partition number (2-128, default 2):
First sector (34-XXXXXX), default = YYYY) or {+-}size{KMGTP}:
Last sector (64-XXXXXX), default = XXXXXX) or {+-}size{KMGTP}: +500MB
Current type is 'Linux filesystem'
Hex code or GUID (L to show codes, Enter = 8300): EF00
```

Finally, allocate the remaining space to the Linux partition:
```
Command (? for help): n
Partition number (3-128, default 3):
First sector (34-XXXXXX), default = YYYY) or {+-}size{KMGTP}:
Last sector (64-XXXXXX), default = XXXXXX) or {+-}size{KMGTP}:
Current type is 'Linux filesystem'
Hex code or GUID (L to show codes, Enter = 8300):
```

Double check the new partition table:
```
Command (? for help): p
```

It should look like to this:
```
Number Start (sector) End (sector) Size Code Name 
1 64 20543 10.0 MiB EF02 BIOS boot partition 
2 20544 1044543 500.0 MiB EF00 EFI System 
3 1044544 62521310 29.3 GiB 8300 Linux filesystem
```

If it's all good, write it to the USB stick and exit gdisk:
```
Command (? for help): w
```

## Format

View the new block layout of the target USB device:
```
lsblk -f /dev/sdX
```

You should now have three blocks on your target USB device: a 10MB block `/dev/sdX1`, a 500MB block `/dev/sdX2`, and block taking all the remaining memory `/dev/sdX3`.

Do not format the `/dev/sdX1` block. This is the BIOS/MBR partion.

Format the 500MB EFI system partition with a FAT32 filesystem:
```
mkfs.fat -F32 /dev/sdX2
```

Format the Linux partition with an ext4 filesystem:
```
mkfs.ext4 /dev/sdX3
```

## Install Base Package Set

Following the Arch Way, this guide intends to install the minimum number of
packages necessary to create a portable working Linux system.

## Mount

Mount the ext4 formatted partition as the root filesystem:
```
mount /dev/sdX3 /mnt
```

Mount the FAT32 formatted ESP partition to `/mnt/boot`:
```
mkdir /mnt/boot
mount /dev/sdX2 /mnt/boot
```

## Pacstrap

Download and install the Arch Linux base packages:
```
pacstrap /mnt base base-devel
```

## fstab

The fstab is used by Linux systems to correctly mount available disk partitions on bootup. The partitions can be identified in the fstab in several ways, and some install methods still use the standard labels (/dev/...) instead of UUIDs. This would surely be a failure point of an install on a USB stick as the standard assigned labels for removable devices are not consistent on each boot.

Toggle the -U tag to enable UUIDs as fstab source identifiers:
```
genfstab -U /mnt >> /mnt/etc/fstab
```

Ensure that the fstab is good:
```
cat /mnt/etc/fstab
```

It should be good to go, but if you see more than the two entries for each of
the mounted partitions, you will need to manually edit `/etc/fstab` and remove
the extra entries:
```
nano /mnt/etc/fstab
```

For additional help manually editing `/etc/fstab`, see the wiki.

## Configure New System

Your USB stick should now contain a persistent Linux system. We still need to configure a few things before it's ready to boot on its own, though.

In addition to the base packages and in the name of ultimate portability, we will also pull and install the required programs to support automatic wired networking, manual wireless networking, all common graphics cards, touchpad input devices, and laptop battery systems. We also need to make some configuration tweaks to ensure that the new system loads support for removable devices before it attempts to access the filesystems, and that it assigns consistent names to network devices regardless of the machine it is boot up on.

## chroot

Begin by chrooting into the new system. Besides the final network settings, everything can be set within the chroot environment:
```
arch-chroot /mnt /bin/bash
```

## Locale

Set the time zone (use tab-completion to discover available entries for region and city) by creating a symbolic link to your chosen region/city (for example, Europe/Zagreb):
```
ln -s /usr/share/zoneinfo/region/city /etc/localtime
```

By default, destination link should not already exit, otherwise use an `-f` option (`--force`).

Generate `/etc/adjtime`:
```
hwclock --systohc
```

Edit `/etc/locale.gen` and uncomment your desired language (for US English, uncomment `en_US.UTF-8 UTF-8`):
```
nano /etc/locale.gen
```

Generate the locale information:
```
locale-gen
```

Set the LANG variable in `/etc/locale.conf`; localeline is the first word of line uncommented in `/etc/locale.gen` (for US English, localeline is `en_US.UTF-8`):
```
echo LANG=localeline > /etc/locale.conf
```

## Hostname

Create the `/etc/hostname` file containing the desired hostname on a single line:
```
echo hostname > /etc/hostname
```

Edit `/etc/hosts` to add an appropriate local hostname entry:
```
nano /etc/hosts
```

Add the line:
```
127.0.1.1    hostname.localdomain    hostname
```

## RAM disk image

In order to boot the Linux Kernel persistently off of a USB device, some adjustments may be necessary to the initial RAM disk image. We need to ensure that block device support is properly loaded before any attempt at loading the filesystem. This not always the way a RAM disk image is configured in a generic Linux installation, and I suspect this may be another one of the failure points in other Linux USB installations out there. To configure a custom RAM disk image, edit the HOOKS variable in `/etc/mkinitcpio.conf`:
```
nano /etc/mkinitcpio.conf
```

Ensure the block hook comes before the filesystems hook and directly after the udev hook like the following:
```
HOOKS="base udev block filesystems keyboard fsck"
```

Now regenerate the initial RAM disk image with the changes made:
```
mkinitcpio -p linux
```

## Network interface names

Arch Linux's basic service manager, systemd, assigns network interfaces predictable names based on the actual device hardware. This is great for just about any other type of install, but can pose some problems for the portable USB installation we're going for. To ensure that the ethernet and wifi interfaces will always be respectively named eth0 and wlan0, revert the Arch Linux USB back to traditional device naming:
```
ln -s /dev/null /etc/udev/rules.d/80-net-setup-link.rules
```

## Journal config

A default installation of Arch Linux is setup with systemd to continuously journal various information about current processes and write that data to storage on disk. For a persistent bootable installation on a flash memory device, however, we can change some options in journald.conf to enable journal keeping entirely in RAM (thus reducing writes to the flash device). To control where journal data is stored, edit `/etc/systemd/journald.conf`:
```
nano /etc/systemd/journald.conf
```

To switch journal data storage to RAM, set the storage variable to volatile by ensuring the following line is uncommented:
```
Storage=volatile
```

As an additional precaution, to ensure the operating system doesn't overfill RAM with journal data, set the max-use variable by adding the line:
```
SystemMaxUse=16M
```

## Mount options

Modern filesystems are able to record various metadata (last accessed, last modified, user rights, etc.) about their files. A default filesystem mount generally keeps track of as much as this information as possible. For a persistent bootable operating system on a flash memory device, however, we should limit some of this record keeping in order to reduce writes to the flash device. Using the noatime mount option in fstab will disable the record keeping of file access times: no writes will occur when a file is read, only when it is modified.

To use the `noatime` mount option for the bootable USB, we'll need to edit the 
fstab:
```
nano /etc/fstab
```

There should be two sets of mount instructions in fstab: an ext4 filesystem mounted at /, and a vfat filesystem mounted at /boot. To disable record keeping of file access times, change the mount options of the ext4 formatted partition by changing the relatime option to noatime.

## Bootloader

To enable booting the target USB stick in both boot modes, two bootloaders will need to be installed. For ease of installation, we'll install GRUB for both modes.

Install the grub and efibootmgr packages:
```
pacman -S grub efibootmgr
```

View the current block devices to determine the target USB device:
```
lsblk
```

Note the target USB device name (without any numbers) `/dev/sdX`.

Setup GRUB for MBR/BIOS booting mode:
```
grub-install --target=i386-pc --boot-directory /boot /dev/sdX
```

Setup GRUB for UEFI booting mode:
```
grub-install --target=x86_64-efi --efi-directory /boot --boot-directory /boot --removable
```

Generate a GRUB configuration:
```
grub-mkconfig -o /boot/grub/grub.cfg
```

## Network support

Install the ifplugd package to configure automatic IP leasing on ethernet devices:
```
pacman -S ifplugd
```

Download the packages to enable wifi support with a basic command line interface:
```
pacman -S iw wpa_supplicant dialog
```

## Video drivers

To support most common GPUs, install all four basic open source video drivers:
```
pacman -S xf86-video-ati xf86-video-intel xf86-video-nouveau xf86-video-vesa
```

## Touchpad support

Install support for standard notebook touchpads:
```
pacman -S xf86-input-synaptics
```

## Battery support

Install support for checking battery charge and state:
```
pacman -S acpi
```

## Root password

Set the root password:
```
passwd
```

## sudo user account

Linux isn't meant to be used with root-user privileges all the time. We need to
create a user account with the ability to selectively run commands as root via
the sudo tool.

Create a new user account newuser:
```
useradd -m -G wheel -s /bin/bash newuser
```

Set newuser password:
```
passwd newuser
```

Edit the `/etc/sudoers` file with the visudo command:
```
EDITOR=nano visudo
```

Give newuser sudo access by adding the line:
```
newuser  ALL=(ALL) ALL
```

To better elevate user privaleges for system wide tasks, we'll also want to install polkit:
```
pacman -S polkit
```

## Reboot new system

Exit the chroot environment:
```
exit
```

Unmount the new USB drive:
```
umount /mnt/boot /mnt
```

Powerdown the computer:
```
poweroff
```

If you booted off a Live USB installation medium, remove it now.

Powerup the computer and use the machine's boot menu to boot off your newly created Arch Linux USB. We still need to configure a few things so login as the root user with the password chosen above.

Check that the network interfaces have been reverted to traditional naming style:
```
ip link
```

LAN devices should appear as eth0 and wireless devices as wlan0.

## netctl-ifplugd

Before enabling ifplugd, copy an example ethernet profile to `/etc/netctl/`:
```
cp /etc/netctl/examples/ethernet-dhcp /etc/netctl/eth0-arch_usb
```

Edit the new profile to ensure the interface is properly named (`Interface=eth0
`):
```
nano /etc/netctl/eth0-arch_usb
```

Start ifplugd to automatically connect to any available wired network:
```
systemctl start netctl-ifplugd@eth0.service
```

Enable automatic wired connection handling on all future sessions:
```
systemctl enable netctl-ifplugd@eth0.service
```

## wifi-menu

We have already installed all the necessary packages to connect to most wifi networks. To scan for available networks and attempt to make a connection, use the simple command line interface `wifi-menu` (`-o` option is for obscure interface where passwords are hidden):
```
wifi-menu -o
```

When you choose and connect to the wifi network you can save it as a profile. To list all network profiles run:
```
netctl list
```

To start or stop a network service from a profile run:
```
sudo netctl [start|stop] [network profile name]
```

If `wifi-menu` doesn't find any networks, make sure your wifi is not hard or soft blocked. Check this with `rfkill`:
```
sudo rfkill list
```

For hard block, use your hardware button to unblock it. For soft block, run:
```
sudo rfkill unblock wifi
``` 

## Network time protocol

Once connected to the internet, turn on the network time protocol to synchronize system time:
```
timedatectl set-ntp true
```

## logout

Logout of the root user account:
```
logout
```

## Installation Complete!

Welcome to Arch Linux on USB. First time users will notice that the base Arch
Linux installation is about as basic as you can get. By default, there is no X
Window System or graphical user interface. Once you install and configure a
window manger or desktop environment Arch Linux can be as graphical as your
heart desires. First time users should definitely read the ArchWiki's general
recommendations to get an idea of what is possible and where to get started
customizing their new USB installations.

For those users who want to setup a fully functioning desktop environment as
quickly as possible, I have written several installer scripts to aid in this
process.

Have fun!


# Additional notes

## Installation from an existing Arch system

If you already have an existing Arch system up and running, you don't have to use live installation medium at all. First, install Arch installation helper scripts:
```
sudo pacman -S arch-install-scripts
```

You now have a pacstrap script which you can use in the same way as previously. Most of the steps from the previous tutorial are identical. Except that you can skip directly to mounting and formating the target USB drive. You don't have to download all of the base packages all over again, you have them already on your working Arch system, so you can run pacstrap with -c option to use the host's package cache:
```
pacstrap -c /mnt base base-devel
```

After arch-chrooting to my newly installed Arch system, I experienced some problems due to (as I understood it) using urxvt terminal. So make sure you arch-chroot from the xterm or some other more standard terminal.

Apparently there is also an option of simply copying the whole Arch system from the USB, which should be even simpler if you just want to copy your existing system. There is some info on Arch Wiki but I didn't try it.
