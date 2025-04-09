# Nix package manager and NixOS

NixOS installation guides
<https://nixos.wiki/wiki/NixOS_Installation_Guide>
<https://nixos.org/manual/nixos/stable/#ch-installation>

Download Nix (package manager) and NixOS (Linux distribution)
<https://nixos.org/download.html>

## Install Nix package manager in Arch Linux

Nix package manager is available in Arch Linux repositories:
<https://wiki.archlinux.org/title/Nix>

There is a native `nix` package in pacman repositories, you can install it with:
```
sudo pacman -Sy nix
```

Check the Arch Wiki for the configuration after installation!

First, enable the nix-daemon service:
```
systemctl enable nix-daemon.service
```

Second, add required users to the `nix-users` group:
```
usermod -aG nix-users matija
```

Third, add a channel and update it:
```
nix-channel --add https://nixos.org/channels/nixpkgs-unstable
nix-channel --update
```

You can also install Nix with the upstream installation script:
```
curl --proto '=https' --tlsv1.2 -sSfL https://nixos.org/nix/install -o nix-install.sh
```

View the installation script:
```
less ./nix-install.sh
```

Run the installation script:
```
./nix-install.sh --daemon
```

## Install NixOS

Prepare USB drive.

Load Croatian keyboard:
```
loadkeys croat
```

Show NixOS installation help:
```
nixos-help
```

Install tmux:
```
nix-env -iA nixos.tmux
```

