# File synchronization with Syncthing

Syncthing allows file synchronization directly between devices, without a central server.

Install Syncthing with:
```
sudo pacman -Syu syncthing
```

Run it with:
```
synchting
```

When you run it for the first time it will create a default synchronization folder `~/Sync` and a config file in `~/.config/syncthing`.

When running, Syncthing can be accessed through a browser-based GUI interface on `http://localhost:8384`. There you can add folders for sharing and see their synchronization status.

## Configuring a new user

In my Arch Linux system I would like to use a copy of my Arch installation as a Syncthing server. The problem is that my Arch installation is an exact copy and will not synchronize between identical devices. To solve this I decided to make a new user on my system which sole purpose will be to run a separate Synchting instance.

Create a new user with home directory:
```
sudo useradd -m sync
```

Change its password:
```
sudo passwd sync
```

Now you can login as the sync user and start the Syncthing instance:
```
su sync
syncthing
```

The browser GUI instance is accessible on the same localhost address `http://localhost:8384`. If I now run an instance as my standard user the GUI will be on another port I guess, and both GUI's will be accessible from my local browser. In general it is possible to run multiple instances of Syncthing, but only one per user because Synchting locks the database to it.

Syncthing can be run as a system or a user service. System service means that Syncthing will run on startup even if the user has no active session. It is intended to be used on a server. Enable and start the system service (assuming sync is the username of the user for which we want to enable the service):
```
systemctl enable --now syncthing@sync.service
```

Syncthing can also be started as an user service, in which case it will run as soon as user is logged in:
```
systemctl enable --now syncthing.service
```

If you have multiple Syncthing instances running on the same local network you might want to differentiate their listening ports. Go to GUI interface on Advanced options, then change the default listening address to:
```
tcp://0.0.0.0:22000,quic://0.0.0.0:22000,dynamic+https://relays.syncthing.net/endpoint
```

And use different ports for different Synchting instances. For example `22010`, `22020` and so on.

