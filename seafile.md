# Seafile cloud storage system

Seafile is an open source cloud storage system. It is available in AUR in three packages: `seafile`, `seafile-server` and `seafile-client` (the first one probably includes the other two).

First I tried to install `seafile-client` from AUR:
```
cd ~/src
git clone https://aur.archlinux.org/seafile-client.git
cd seafile-client
makepgk -sri
```

But there was a problem with this installation. Official installation instructions have no additional information on installation from AUR:
<https://help.seafile.com/syncing_client/install_linux_client/>

But the discussion under AUR package explained that version 8.0.3 has wrong sha256 checksum:
<https://aur.archlinux.org/packages/seafile-client/>

This can be changed manually in PKGBUILD, as explained in the comments:

    Clone packaging instructions: $ git clone https://aur.archlinux.org/seafile-client.git
    $ cd seafile-client
    Download the release from the official github page: $ wget -O seafile-client-8.0.3.tar.gz https://github.com/haiwen/seafile-client/archive/v8.0.3.tar.gz
    Create the checksums for it: $ sha256sum seafile-client-8.0.3.tar.gz
    Edit the PKGBUILD to match the shasum from Step 4 (line ~24)
    Install the package: $ makepkg -si

However, this still didn't work for me:-/ So I decided to install `seafile` package from AUR:
```
cd ~/src
git clone https://aur.archlinux.org/seafile.git
cd seafile
makepkg -sri
```

This had similar problems, including some missing dependencies. So I installed `libsearpc` from AUR:
```
cd ~/src
git clone https://aur.archlinux.org/libsearpc.git
cd libsearpc
makepkg -sri
```

A well as python-future from official repository:
```
sudo pacman -Syu python-future
```

There was again problem with the wrong checksum, so I calculated it again:
```
sha256sum seafile-8.0.3.tar.gz
```

And replace the checksum in PKGBUILD under sha256sums variable (line 29) - there are two of them in the array, the first one is for `seafile-8.0.3.tar.gz`.

You can now install seafile normally with `makepgk -sri`.

The CLI client is available with `seaf-cli` command.

## Donwloading and synching with the existing library on server

Use these instruction on how to download and synchronize with a Seafile library on a remote server using Seafile CLI client on Linux:
<https://help.seafile.com/syncing_client/linux-cli/>

Browse to the library on the Web to get its ID, it will look like `f4962ce9-ba07-47b8-a83a-73dd96c2ebfd`.

Initialize configuration/settings folder for Seafile:
```
mkdir ~/.config/seafile-client            # create the settings folder
seaf-cli init -d ~/.config/seafile-client  # initialise seafile client with this folder
seaf-cli start
```

Now download and synchronize the remote library to your local machine - the ID of the library is the one that you found in URL above. You will be asked for your user password on the server: 
```
seaf-cli download -l "f4962ce9-ba07-47b8-a83a-73dd96c2ebfd" -s "https://seafile.server.com" -d ~/share/seafile -u username
```

You can check the status of synchronization with:
```
seaf-cli status
```

You now have a local folder which is synchronized with the remote server!

If you want you can also create a systemd service for Seafile CLI client to run automatically at startup:
<https://manual.seafile.com/deploy/start_seafile_at_system_bootup/>

## Troubleshooting

In January 2022 the `seaf-cli start` is not working anymore, it reports `ModuleNotfoundError: No module named 'seafile'`. This is reported on the AUR webpage as well but with no solution:
<https://aur.archlinux.org/packages/seafile/>

I cloned the `seafile` AUR package again and install it, there were no problems but now the error message when running `seaf-cli start` is `ModuleNotFoundError: No module named 'pysearpc'`. These are Python bindings for libsearpc which should be installed by default, but they are apparently not. I installed libsearpc through AUR and it is on the newest version.

Update June 2022 - I reinstalled libsearpc from AUR and now the Seafile is starting fine!

To install libsearpc:
```
cd ~/src/
git clone https://aur.archlinux.org/libsearpc.git
cd libsearpc
makepkg -sri
```

To just update it:
```
cd ~/src/libsearpc
git pull
makepkg -sri
```

Now you can start Seafile daemon with `seaf-cli start`.

