# Power management in Arch Linux

Poweroff computer: `poweroff`
Reboot: `reboot`
Suspend to RAM (sleep): `systemctl suspend`

## Power management on laptop

Default behavior when closing the laptop lid is to go to suspend. This can be changed in `/etc/systemd/logind.conf`, find the appropriate line and change it to ignore:
```
HandleLidSwitch=ignore
```

If you want changes to take effect immediatelly you can run (requires sudo password):
```
systemctl restart systemd-login
```

You will be logged out from your current X session, but after that the closing of the lid does not trigger suspend, it only turns off the screen.

## CPU frequency scaling

CPU frequency scaling on Arch Linux Wiki
<https://wiki.archlinux.org/title/CPU_frequency_scaling>

Prevent Your Laptop From Overheating With Thermald And Intel P-State 
<http://www.webupd8.org/2014/04/prevent-your-laptop-from-overheating.html?ref=itsfoss.com>

## TLP for power saving

TLP is a feature-rich command line utility for Linux, saving laptop battery power without the need to delve deeper into technical details.
<https://wiki.archlinux.org/title/TLP>
<https://linrunner.de/tlp/introduction.html>
