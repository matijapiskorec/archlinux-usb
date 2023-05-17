# OneDrive client for Linux

Install onedrive-abraunegg to synchronize OneDrive folders to your Arch Linux machine:
<https://github.com/abraunegg/onedrive>
<https://aur.archlinux.org/packages/onedrive-abraunegg>
<https://abraunegg.github.io/>

To install:
```
cd ~/src/
git clone https://aur.archlinux.org/onedrive-abraunegg.git
cd onedrive-abraunegg/
makepkg -sri
```

Usage of onedrive:
<https://github.com/abraunegg/onedrive/blob/master/docs/USAGE.md>

List help and all options:
```
onedrive --help
```

You can create the default config file with all possible options commented-out:
```
wget https://raw.githubusercontent.com/abraunegg/onedrive/master/config -O ~/.config/onedrive/config
```

Unfortunately, I cannot change the destination directory to `~/share/onedrive` with either of these two commands:
```
onedrive destination-directory "~/share/onedrive" --synchronize
onedrive --destination-directory "~/share/onedrice" --synchronize
```

Hmmm, it seems that this is not the correct way of changing the local synchronization folder. It should be done with `--syncdir` option (specify the local directory used for synchronization to OneDrive). 

Anyway, for now I run it like this to initialize the `~/OneDrive` directory:
```
onedrive --synchronize
```

Upon first login it will give you a web link which you should copy to your browser and authentificate. Once the authentification in browser is done you can copy the resulting URI (the webpage itself will be empty) back into the terminal.

My OneDrive was empty and I only had shared folders. Follow the instructions here for synchronizing shared folders:
<https://github.com/abraunegg/onedrive/blob/master/docs/BusinessSharedFolders.md>

You have to first list shared folders for your account:
```
onedrive --list-shared-folders
```

It will output something like:
```
Listing available OneDrive Business Shared Folders:
---------------------------------------
Shared Folder:   SharedFolder0
Shared By:       Firstname Lastname
---------------------------------------
Shared Folder:   SharedFolder1
Shared By:       Firstname Lastname
```

Note the shared folder names that you wish to synchronize. Now create a file `~/.config/onedrive/business_shared_folders` and add each folder you wish to synchronize to separate lines:
```
SharedFolder0
SharedFolder1
```

Check whether shared folders are properly registered with:
```
onedrive --display-config
```

Now synchronize shared folders with:
```
onedrive --synchronize --sync-shared-folders --verbose
```

This will not work because we changed the `business_shared_folder`, and so it asks us to `--resync` (some configuration changes require a resync). So I ran the previous command with this option and then it synced:
```
onedrive --synchronize --sync-shared-folders --verbose --resync
```

Create a sharing link for a file with:
```
onedrive --create-share-link <path/to/file>
```

By default this will be a read-only link. To make this a read-write link, use the following command:
```
onedrive --create-share-link <path/to/file> --with-editing-perms
```

## Managing multiple accounts

onedrive is a completelly command-line utility, so it should be possible to somehow manage multiple Microsoft accounts. There is also a GUI utility which apparently has management of multiple accounts out of the box:

OneDriveGUI
<https://github.com/bpozdena/OneDriveGUI>

Here are the instructions for the CLI client:
<https://github.com/abraunegg/onedrive/wiki/OneDrive-Client-Multi-Account-Configuration-Assistance>

To manage multiple accounts, follow these instructions:

First, each account must its own configuration directory, for example:
```
~/.config/onedrive-Personal
~/.config/onedrive-Work
```

Copy the default configuration file to both:
```
wget https://raw.githubusercontent.com/abraunegg/onedrive/master/config -O ~/.config/onedrive-Personal/config
wget https://raw.githubusercontent.com/abraunegg/onedrive/master/config -O ~/.config/onedrive-Work/config
```

Second, each account needs to have its own sync directory. Uncomment the `sync_dir` line and add corresponding directories to each of the configs:
```
sync_dir = "~/share/onedrive/Personal"
sync_dir = "~/share/onedrive/Work"
```

You can also copy any specific files, for example `business_shared_folders` file.

Third, verify that two accounts see their corresponding directories:
```
onedrive --confdir="~/.config/onedrive-Personal" --display-config
onedrive --confdir="~/.config/onedrive-Work" --display-config
```

Fourth, test the client configuration with `--dry-run`:
```
onedrive --confdir="~/.config/onedrive-Personal" --synchronize --sync-shared-folders --verbose --dry-run
onedrive --confdir="~/.config/onedrive-Work" --synchronize --sync-shared-folders --verbose --dry-run
```

Finally, run the client synchronization with the appropriate configuration:
```
onedrive --confdir="~/.config/onedrive-Personal" --synchronize --sync-shared-folders --verbose 
onedrive --confdir="~/.config/onedrive-Work" --synchronize --sync-shared-folders --verbose 
```

You can put aliases so that you always call onedrive with appropriate configuration directory, for example in my, for example in my Fish config `~/.config/fish/config.fish`:
```
alias onedrive-personal 'onedrive --confdir="~/.config/onedrive-Personal"'
alias onedrive-work 'onedrive --confdir="~/.config/onedrive-Work"'
```

To monitor and sync the folders, and also making sure that you are syncing the shared folders as well, just run:
```
onedrive-personal --sync-shared-folders --monitor
onedrive-work --sync-shared-folders --monitor
```

You can make file sync faster, especially from remote to your local (the reverse is usually very fast as the monitor uploads local files as soon as they are changed) by changing this line in your config:
```
monitor_interval = "10" 
```

The default value is 300, meaning each 5 minutes (300 seconds) there will be a full sync check. See documentation for this option:
<https://github.com/abraunegg/onedrive/blob/master/docs/USAGE.md#monitor_interval>

## Alternative OneDrive clients

onedriver
<https://github.com/jstaf/onedriver>
<https://aur.archlinux.org/packages/onedriver>

rclone
<https://github.com/rclone/rclone>
<https://archlinux.org/packages/community/x86_64/rclone/>
<https://rclone.org/>

