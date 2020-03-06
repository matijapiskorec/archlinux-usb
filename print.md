# Printing on Arch Linux

Install CUPS open source printing system:
```
sudo pacman -Syu cups cups-pdf
```

Enable and start cups service:
```
sudo systemctl enable --now org.cups.cupsd.service
```

You can now go to your browser to configure printers:
```
http://localhost:631
```

## Some command line options

List the devices: `lpinfo -v`
List the models: `lpinfo -m`
Check the status: `lpstat -s`

## Tips and tricks

If you have problems printing with HP printer (PCL XL Error) make sure that you are using PCL4/5 drivers and not PCL6 drivers.

If your printer supports duplexer jobs (two-sided printing) you can set the appropriate option in the `Options Installed` settings as `installed`.


