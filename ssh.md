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
    HostName     server-address
    Port         port
    User         user
    IdentityFile ~/.ssh/key
```

You can now connect with:
```
ssh myserver
```

## SSH access with a public key

Generate key with rsa method:
```
ssh-keygen -t rsa
```

Copy the generated key to server (if you have more keys then specify a key with `-i` option):
```
ssh-copy-id user@host
```

You can try to ssh to the server. ssh will prompt you for the key password (private key is encrypted!):
```
ssh user@server
```

Check that your public key is added to `~/.ssh/authorized_keys`:
```
cat ~/.ssh/authorized_keys
```

## Adding keys to ssh-agent so you don't have to type password

Run ssh-agent which will allow you to put keys in cache so you don't have to enter keyphrase:
```
eval `ssh-agent`
```

Add key to cache for eight hours and then delete it (so that someone cannot steal the key from memory):
```
ssh-add -t 8h
```

List all keys that are added to the ssh-agent:
```
ssh-add -L
```

Delete all keys currently in ssh-agent:
```
ssh-add -D
```

## Simplifying key management with keychain

ssh-agent relies on environment variables which are not shared between bash sessions, so each time you start a new terminal you have to run it and add keys again. This is solved with keychain program: 
```
sudo pacman -Syu keychain
```

Put the following line in `.bashrc` to start keychain in each new bash session. It will either run a new ssh-agent or inherit from an existing one:
```
eval $(keychain --eval --quiet --noask)
```

At this point you didn't yet added any keys to the keychain (you can check this with `ssh-add -L`). You can add keys with:
```
keychain id_rsa
```

Or, if you want, you can add a key with a time limit in minutes, after which it is deleted from keychain:
```
keychain --timeout 30 id_rsa
```

Clear all keys currently in keychain (for example, before logout):
```
keychain --clear
```

You can also use `ssh-add` to list all keys currently added to keychain (keychain is just a manager for ssh-agent!):
```
ssh-add -L
```

## Tunneling

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

## Tunel to a server through intermediary

You want to tunnel to a server2 through an intermediary server1. Setup your ssh config file in the following way:
```
Host server1
	HostName server1.com
	User user1
	IdentityFile ~/.ssh/id_rsa

Host server2
	HostName server2.com
	User user2
	IdentityFile ~/.ssh/id_rsa
	ProxyJump server1
```

You can copy your local ssh key to server2 using:
```
ssh-copy-id -i ~/.ssh/id_rsa server2
```

# Mount remote directories with sshfs

Install sshfs for mounting remote directories through ssh:
```
sudo pacman -Syu sshfs
```

You can now mount remote directories locally:
```
sshfs user@host:remote_directory local_directory
```

You can now edit directory locally and the changes will persist remotelly, and vice versa. You can unmount with fusermount3 (installed automatically with sshfs):
```
fusermount3 -u local_directory
```

Can we unmount with umount?
```
sudo umount local_directory
```

Remote editing file on remote
```
vim scp://<HOST>//<PATH>
```
