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

