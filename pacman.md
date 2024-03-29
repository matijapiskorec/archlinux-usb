# Pacman package manager for Arch Linux

Update pacman:
```
sudo pacman -Sy
```

Update the whole system:
```
sudo pacman -Syu
```

Install a package:
```
sudo pacman -S [package name]
```

However, it is recommended you update your system along with every package install:
```
sudo pacman -Syu [package name]
```

Check all explicitly installed packages (add `-q` to list only package names):
```
sudo pacman -Qe | less
```

Check all native packages (installed from the sync database): 
```
sudo pacman -Qn | less
```

Check whether a specific package is installed:
```
pacman -Qi [package name]
```

Check which packages need to be updated (in order to get the newest state it's best to first update the package database with `sudo pacman -Sy`):
```
pacman -Qu
```

Find out optional dependencies for a program:
```
sudo pacman -Si [program]
```

Install optional dependencies for the specific program:
```
sudo pacman -S --asdeps [optional dependencies]
```

List orphaned packages, dependencies that are not needed by any other package anymore:
```
pacman -Qdt
```

Install packages from a list `pkglist.txt` (produced by running pacman with `-Qe`):
```
sudo pacman -S --needed - < pkglist.txt
```

Remove a package:
```
sudo pacman -R [program]
```

Remove a package along with all of its dependecies which are not explicitly required by any other installed package (`-s`), and system config files (`-n`):
```
sudo pacman -Rns [program]
```

Clean package cache (old packages which are not needed anymore):
```
sudo pacman -Sc
```

Include a multilib repository which contains 32-bit packages. Uncomment the following lines in the pacman config file `/etc/pacman.conf`:
```
[multilib]
Include = /etc/pacman.d/mirorlist
```

You will need to run `sudo pacman -S` to synchronize package cache in order to make the new packages visible.

## Failed to commit transaction (conflicting files) error

If you see this error when updating Pacman packages, followed by a list of files which "exist in filesystem", this means that you installed some programs manually (without Pacman) and these installations are now conflicting with the ones in official Pacman repos. One case where this mihgt happen is when you install Python packages through pip by using root privileges, instead of using virtual environment and installing them locally. This happened to me with python-psutil package, which I installed globally through pip and also tried to update through Pacman.

You can check whether a file is owned by any package:
```
pacman -Qo /path/to/file
```

If you get a message that no package owns this file, and the file is somewhere where Pacman might want to install a package (for example `/usr/lib/python3.8/` or similar) then this might cause a conflict. The solution is to uninstall the package manually and then initiate Pacman upgrade. For example, in the case of python-psutil which exist both as a Pacman package and as a pip package, first check globally installed pip packages:
```
pip freeze
```

If psutil is there, uninstall it through pip:
```
pip uninstall psutil
```

Now you can install python-psutil through Pacman and everything should be ok.

As a general rule - never use pip with root (sudo) privileges, always install it into virtual environment or locally. Keep your global pip package repository clean. In this way you can install any of the pyhton-related packages from Pacman repository safely, and they will be available globally for you programs to use, and the ones from pip will be available within your virtual environment for your projects.

More information on this error:
<https://wiki.archlinux.org/index.php/Pacman#.22Failed_to_commit_transaction_.28conflicting_files.29.22_error>

## Mirrorlists

Pacman depends on the mirrors to synchronize packages. Currently used mirror list can be found in `/etc/pacman.d/mirrorlist`. You can also obtain up-to-date mirrorlist from the following page:
<https://archlinux.org/mirrorlist/>

Or you can install and use reflector, a Python program for retrieving mirrorlists:
```
sudo pacman -Syu reflector
```

Now you can generate a mirrorlist with reflector:
```
reflector > /tmp/mirrorlist
sudo mv /tmp/mirrorlist /etc/pacman.d/mirrorlist
```

NOTE (February 2021): Apparently the mirrorlist changed since my initial Arch Linux install, and none of the mirrors in the list were responisive - the `sudo pacman -Syu` command just reported "Nothing to do." I checked the `/etc/pacman.d/` folder and there were both `mirrorlist` as well as `mirrorlist.pacnew` which was created recently and which corresponded to the mirrorlist I could obtain from Arch website. So I just backuped the old mirrorlist and replaced it with the new one:
```
sudo cp /etc/pacman.d/mirrorlist /etc/pacman.d/mirrorlist.backup
sudo cp /etc/pacman.d/mirrorlist.pacnew /etc/pacman.d/mirrorlist
sudo vim /etc/pacman.d/mirrorlist
```

And then I manually uncommented mirrors which seemed most appropriate (worldwide and in central Europe).
 
## Corrupted signatures

If you didn't update your system with `sudo pacman -Syu` for a while it's quite likely that you will get corrupted signatures. Just run before updating the system:
```
sudo pacman -Sy archlinux-keyring && pacman -Su
```

This problem is described here:
<https://wiki.archlinux.org/title/Pacman/Package_signing#Upgrade_system_regularly>

## Downgrading a package

You can donwgrade a package manually from cache if the version is still there:
```
sudo pacman -U file:///var/cache/pacman/pkg/package-old_version.pkg.tar.type
```

Note that `type` will be `xz` for older package builds, and `zst` for those following the 2020 change.

Add the package to the `IgnorePkg` option in the `/etc/pacman.conf` until the problematic update is resolved:
```
[options]
# Pacman won't upgrade packages listed in IgnorePkg and members of IgnoreGroup
IgnorePkg   = package
```
