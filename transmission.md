# Downloading torrent files with transmission client

Install transmission cli client for downloading torrents:
```
sudo pacman -Syu transmission-cli
```

Start the transmission daemon:
```
transmission-daemon
```

By default, transmission web interface is accessible at `http://localhost:9091`.

You may want to check settings first:
```
transmission-daemon --dump-settings
```

And maybe change the download directory (using absolute path):
```
transmission-daemon --download-dir="/home/matija/tmp/download"
```

## Using transmission command line interface

Transmission CLI interface is easy to use:
<https://cli-ck.io/transmission-cli-user-guide/>

First, it is maybe useful to set aliases for the transmission. If you are using bash, in `.bashrc`:
```
alias tsd="transmission-daemon"
alias tsr="transmission-remote"
```

Or, if you are using fish shell, in `fish.config`:
```
alias tsd 'transmission-daemon'
alias tsr 'transmission-remote'
```

Start the transmission daemon: `tsd`
List current torrents: `tsr -l`
Add a torrent from file or magnetic link: `tsr -a "[MAGNET-URI]"`
Add a torrent from file or magnetic link but start paused: `tsr -a --start-paused "[MAGNET-URI]"`
Remove a torrent from the list using its ID: `tsr -t ID -r`
Remove all torrents from the list: `tsr -t all -r`
Remove all torrents and delete their files: `tsr -t all -rad`
Get the file list for all torrents: `tsr -t all -f`
Stop all torrents: `tsr -t all -S`
Start all torrents: `tsr -t all -s`
Shutdown the transmission daemon: `tsr --exit`

## Automatically watching with watch

transmission-remote gives a static output and you need to run it multiple times to check the status. You can do this automatically every 2 seconds with the watch command:
```
watch transmission-remote -l
```

Note that you cannot use aliases within watch, this is why we need to specify the full command transmission-remote!

