# Trezor hardware wallet

Download Trezor Bridge that communicates between the browser (only Chrome and Firefox are supported) and you Trezor hardware wallet:
<https://wallet.trezor.io/#/bridge>

You can only download them as DEB and RPM packages. DEB package is basically just a binary stored in an archive, you can unpack it and just run the executable:
```
ar xv trezor-bridge_2.0.30_amd64.deb 
tar xvfz *.gz
```

I copied the binary in my local home bin folder:
```
cp ./usr/bin/trezord ~/bin
trezord&
```

Now you can plug in your Trezor wallet and go to <https://wallet.trezor.io/#/> to use it.

You can also compile Trezor Bridge yourself from Go source, but I had problem with that:-/
<https://github.com/trezor/trezord-go>
<https://eli5.it/setting-up-your-trezor-hardware-wallet-on-arch-linux/>

There is also Trezor Bridge package in AUR which is not maintained anymore:
<https://aur.archlinux.org/packages/trezor-bridge-bin/>

## Trezor Suite

You can also use Trezor Suite:
<https://suite.trezor.io/>

Download the AppImage, copy it to your local bin folder and make it executable:
```
cp ~/tmp/download/Trezor-Suite-[version]-x86_64.AppImage ~/bin/
cd ~/bin
chmod +x ./Trezor-Suite-[version]-x86_64.AppImage
./Trezor-Suite-[version]-x86_64.AppImage

