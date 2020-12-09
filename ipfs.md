# IPFS - Interplanetary File System

Arch Linux documentation on IPFS:
<https://wiki.archlinux.org/index.php/IPFS>

Install IPFS on Arch Linux:
```
sudo pacman -Syu go-ipfs
```

To start using IPFS you first have to initialize it which will create `~/.ipfs` directory with all neccessary files:
```
ipfs init
```

Now you can start IPFS daemon which starts your IPFS node:
```
ipfs daemon
```

You can view the status through web interface:
<localhost:5001/webui>

A full CLI reference for IPFS:
<https://docs.ipfs.io/reference/cli/#ipfs>

