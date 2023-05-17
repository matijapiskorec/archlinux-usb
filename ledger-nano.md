# Ledger Nano X crypto hardware wallet

Install Ledger Live to interact with your Ledger Nano X crypto hardware wallet:
<https://www.ledger.com/start>

The Linux version comes as an AppImage, I just put it in my `~/bin` folder, add executable privileges with `chmod +x ledger-live-desktop-2.33.1-linux-x86_64.AppImage` and run it.

There were some recognition issues while checking whether device was genuine, the solution is here:
<https://support.ledger.com/hc/en-us/articles/115005165269>

Basically you have to change the udev rules with this command:
```
wget -q -O - https://raw.githubusercontent.com/LedgerHQ/udev-rules/master/add_udev_rules.sh | sudo bash
```

This broke my keyboard layout, in particular switching CapsLock and Esc key, so I just run the appropriate command again:
```
setxkbmap -option caps:swapescape
```

