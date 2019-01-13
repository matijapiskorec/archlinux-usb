# Manage disks with modern udisks2 utility (instead of mount)

Install udisks2 package:
```
sudo pacman -S udisks2
```

View help and available disks on the system:
```
udisksctl help
udisksctl dump
```

Mount a desired disk (in this case, just a specific partition within a disk!):
```
udisksctl mount -b /dev/sda2
```

Disk is now mounted in `/run/media/matija/` and user can access it normally.

To unmount it:
```
udisksctl unmount -b /dev/sda2
```

In order to write to a NTFS volume (Windows filesystem) you need to install `ntfs-3g` package, as Arch Linux only support reading from NTFS:
```
sudo pacman -Syu ntfs-3g
```

Some udisksctl actions require special permissions, for example mounting internal HDD drives. These permissions are managed by polkit, you can add rules to:
```
/etc/polkit-1/rules.d/10-auth.rules
/usr/share/polkit-1/rules.d/10-auth.rules
```

Names of the `.rules` files don't matter, numbers in front determine the order of checking the rules. The most basic rules allow udisksctl to mount devices without authentication for users in certain group (here in `wheel`):
```
polkit.addRule(function(action, subject) {
   if ((action.id == "org.freedesktop.udisks2.filesystem-mount-system" ||
        action.id == "org.freedesktop.udisks2.filesystem-mount") &&
       subject.isInGroup("wheel")) {
       return polkit.Result.YES;
   }
});
```

Advanced rules allow restricting access only to certain devices, identified by model or vendor. For more info check `man polkit`. An example with more options can be found in [udiskie documentation](https://github.com/coldfix/udiskie/wiki/Permissions):
```
polkit.addRule(function(action, subject) {
 var YES = polkit.Result.YES;
 var permission = {
   "org.freedesktop.udisks2.filesystem-mount": YES,
   "org.freedesktop.udisks2.encrypted-unlock": YES,
   "org.freedesktop.udisks2.eject-media": YES,
   "org.freedesktop.udisks2.power-off-drive": YES
 };
 if (subject.isInGroup("wheel")) {
   return permission[action.id];
 }
});
```

Rules above can have suffixes depending on the location of the device or who is issuing a command. Rules of format `org.freedesktop.udisks2.XXX-system` are required for internal devices (for example, internal HHD drive). Rules of format `org.freedesktop.udisks2.XXX-other-seat` are required when a device is accessed from another login session (for example, over a ssh, systemd service or a cron job).
