# SSH access to remote servers

Install `openssh` package:
```
sudo pacman -Syu openssh
```

To check the IP address of your machine run:
```
ip address
```

To check IP's of neighbors run:
```
ip neighbor
```

## Connecting to a remote ssh server

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

## Setup a ssh server

To setup a ssh server first edit the configuration in `/etc/ssh/sshd_config`. Reasonable options to uncomment and set are:
```
AllowUsers [USER]
PermitRootLogin no
Port 22
```

Then run systemd service either as start (just for this session) or enable (to start automatically at boot):
```
sudo systemctl [start|enable] sshd.socket
```

Enabling `sshd.socket` service at boot allows the computer to be used as a headless server, after appropriate networking setup.

If `sshd.socket` service is active it should be listed under `user.slice` section when you run systemctl command:
```
systemctl
```

## SSH access with a public key

Generate key with rsa method:
```
ssh-keygen -t rsa
```

Copy the generated key to server (if you have more keys then specify a key with `-i` option, otherwise all keys will be added!):
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

List all keys currently added to keychain (you can also use ssh-add with the same option because keychain is just a manager for ssh-agent!):
```
keychain -L
ssh-add -L
```

## Tunneling

Tunnelling local-remote:
```
ssh -L<PORT>:<HOST>:<HOSTPORT>
```

For example:
```
ssh -L8080:localhost:22 some.server
```

Now when we run `ssh localhost 8080` we'll connect to some.server! Instead of `localhost` you can put and other machine that's on the same network as some.server. Just make sure no other service listens on port 8080!

Tunneling remote-local
```
ssh -R<PORT>:<HOST>:<HOSTPORT>
```

SOCKS proxying:
```
ssh -D<PORT> <HOST>
```

In your browser go to manual proxy settings and setup proxy. In Firefox go to network settings, add `127.0.0.1` as proxy address, port `<PORT>` and select `SOCKS5` as protocol. This is great for connecting from public places as SSH is encrypted and safe. You can also use it if the webpage does not allow connection from outside of certain network. You have to setup GatewayPorts on client to make it work.

You can also use curl through proxy in the same way, for example to download a pdf file from behind a paywall:
```
curl -x socks5://127.0.0.1:<PORT> <URL> --output [FILE NAME].pdf
```

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

If fusermount3 and regular umount report error that target is busy or that some other device is using the mount point, you can try lazy umount which should work:
```
sudo umount -l local_directory
```

However, this is not a real unmount and it will be impossible to remount the network disk later on! See comments on the umount man pages:

    A system reboot would be expected in near future if you're  going  to  use  this  option  for  network filesystem  or  local filesystem with submounts.  The recommended use-case for umount -l is to prevent hangs on shutdown due to an unreachable network share where a normal umount will hang due to a  downed server or a network partition. Remounts of the share will not be possible.

Remote editing file on remote:
```
vim scp://<HOST>//<PATH>
```

If you have a corresponding entry in `~/.ssh/config` for the server and your username you can use this:
```
vim scp://server//home/user/file.txt
```

Otherwise you have to specify full username and server URL:
```
vim scp://user@server//home/user/file.txt
```

Secure copy file from your local machine to remote:
```
scp /home/user/image*.jpg user@myhost.com:/home/user
```

## Check open ports and ports in use

Check which ports are in use:
```
sudo lsof -i -P -n
```

Check if specific port is in use:
```
sudo lsof -i:8000
```

Check which ports are listening for connections:
```
sudo lsof -i -P -n | grep LISTEN
```

## Execute a command on remote server

You can can execute a command on remote server and receive its output via ssh. For example, you can check the memory usage of the remote machine with the free command:
```
ssh user@server 'free'
```

To check the top 20 processes which are using the most CPU's on the remote machine, you can run this command:
```
ssh user@server "ps -eo pcpu,pmem,pid,user,args | sort -k 1 -r | head -20"
```

Similarly, if you want to check which processes are using the most memory, just put pmem option on the first place in the command above:
```
ssh user@server "ps -eo pmem,pcpu,pid,user,args | sort -k 1 -r | head -20"
```


