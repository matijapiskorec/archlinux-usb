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


