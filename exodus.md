# Exodus crypto wallet

Download and install Exodus crypto wallet from AUR:
```
cd ~/src
git clone https://aur.archlinux.org/exodus.git
cd exodus
makepkg -sri
```

Now you can run Exodus desktop app with `exodus`!

To update Exodus just pull the changes with git and rebuild the package:
```
cd ~/src/exodus
git pull
makepgk -sri
```

## Syncing Exodus wallet to different devices

There is a mobile version of Exodus wallet as well as desktop. You can sync between them if you have both. What is important to know to/from which device you are syncing, as you are basically overwriting one device! While syncing devices you can either show or scan QR code on the device:
- The device which shows QR code is the main device which you want to preserve (presumably because it as coins).
- The device which scans QR code is the new (presumably empty) device to which you want to sync the main device. It's backup phrase will be overwritten with the main device! 

I first created the Exodus on iOS and saved the backup phrase. I then installed Exodus desktop on my Arch Linux and synced the devices, but because my laptop does not have a camera I showed the QR code on laptop and scanned it on my phone - this essentially overwritten the iOS wallet with the desktop wallet! There was no damage because both wallets were empty. The backup phrase for my mobile Exodus wallet now changed to the one from desktop.

## Using Trezor with Exodus

You can use your Trezor hardware wallet with Exodus, just make sure you are running Trezor Bridge daemon. Just run:
```
trezord
```

Plug your Trezor and fire Exodus! Trezor will appear as a separate wallet inside Exodus, with the same interface.

## Importing a private key

If you have a private key (for example, from a paper wallet) you can import it by clicking the three dots in the upper right menu, then selecting "Move Funds". Just type in the private key or scan the QR code - for me scanning QR code does not work for some reason so I had to type it in manually.


