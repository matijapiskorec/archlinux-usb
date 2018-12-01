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


Generate key:
```
ssh-keygen
```

Copy public key to server:
```
ssh-copy-id
```

Put a key to `ssh-agent` (cache) so you don't have to enter keyphrase:
```
eval `ssh-agent`
ssh-add -L
```

Add key to cache for eight hours and then delete it (so that someone cannot steal the key):
```
ssh-add -t 8h
```

Tunnelling local->remote:
```
ssh -L<PORT>:<HOST>:<HOSTPORT>
```

For example:
```
ssh -L8080:localhost:22 some.server
```

Now when we run `ssh localhost 8080` we'll connect to some.server! Instead of `localhost` you can put and other machine that's on the same network as some.server. Just make sure no other service listens on port 8080!

Tunneling remote->local
```
ssh -R<PORT>:<HOST>:<HOSTPORT>
```

SOCKS proxying:
```
ssh -D<PORT> <HOST>
```

In your browser go to manual proxy settings and setup proxy. In Firefox go to network settings, add `127.0.0.1` as proxy address, port `<PORT>` and select `SOCKS5` as protocol. This is great for connecting from public places as SSH is encrypted and safe. You can also use it if the webpage does not allow connection from outside of certain network. You have to setup GatewayPorts on client to make it work.

Poor's man VPN. We have to be root on both machines:
```
ssh -w0:0 root@some.server
```

sshfs - secure remote mounts:
```
sshfs host:remote_directory local_directory
sudo umount local_directory
```

Remote editing file on remote
```
vim scp://<HOST>//<PATH>
```
