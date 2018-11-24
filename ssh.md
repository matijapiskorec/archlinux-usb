# SSH access to remote servers

Install `openssh` package:
```
sudo pacman -Syu openssh
```

Connect to a server:
```
ssh -p [PORT] [USERNAME]@[SERVER]
```

Add ssh configuration to `~/.ssh/config`:
```
# global options
User user

# host-specific options
Host myserver
    HostName server-address
    Port     port
```

You can now connect with:
```
ssh myserver
```
