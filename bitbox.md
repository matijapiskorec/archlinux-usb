# BitBox hardware wallet

Download BitBox desktop app that manages your hardware wallet:
<https://shiftcrypto.ch/download/>

Go to Linux and then Linux64 Other. The app is a simple AppImage. After download copy it to your local bin folder, make executable and run:
```
cp ~/tmp/download/BitBox-[version]-x86_64.AppImage ~/bin/
cd ~/bin
chmod +x ./BitBox-[version]-x86_64.AppImage 
./BitBox-[version]-x86_64.AppImage 
```

If your device is not recognized you need to manually adjust the USB permissions. Execute these commands as root (run `su`):
```
printf "SUBSYSTEM==\"usb\", TAG+=\"uaccess\", TAG+=\"udev-acl\", SYMLINK+=\"bitbox02_%%n\", ATTRS{idVendor}==\"03eb\", ATTRS{idProduct}==\"2403\"\n" | sudo tee /etc/udev/rules.d/53-hid-bitbox02.rules > /dev/null && printf "KERNEL==\"hidraw*\", SUBSYSTEM==\"hidraw\", ATTRS{idVendor}==\"03eb\", ATTRS{idProduct}==\"2403\", TAG+=\"uaccess\", TAG+=\"udev-acl\", SYMLINK+=\"bitbox02_%%n\"\n" | sudo tee /etc/udev/rules.d/54-hid-bitbox02.rules > /dev/null
printf "SUBSYSTEM==\"usb\", TAG+=\"uaccess\", TAG+=\"udev-acl\", SYMLINK+=\"dbb%%n\", ATTRS{idVendor}==\"03eb\", ATTRS{idProduct}==\"2402\"\n" | sudo tee /etc/udev/rules.d/51-hid-digitalbitbox.rules > /dev/null && printf "KERNEL==\"hidraw*\", SUBSYSTEM==\"hidraw\", ATTRS{idVendor}==\"03eb\", ATTRS{idProduct}==\"2402\", TAG+=\"uaccess\", TAG+=\"udev-acl\", SYMLINK+=\"dbbf%%n\"\n" | sudo tee /etc/udev/rules.d/52-hid-digitalbitbox.rules > /dev/null
```

I created device password and recovery password with pass:
```
pass generate -n BitBox/device-password 8
pass generate -n BitBox/recovery-password 8
```

Device password is needed for accessing the device and can be changed. Recovery password is needed for recovery from your SD card and cannot be changed!

