# Firefox web browser

Install Firefox web browser:
```
sudo pacman -Syu firefox
```

## Firefox performance tweaks

Firefox caches loaded objects so that they don't have to be retrieved online. This significantly increases reads/writes to disk, which is not always desirable if we are running our Arch Linux installation from an USB drive. To turn off disk cache in Firefox follow this [guide](https://wiki.archlinux.org/index.php/Firefox/Tweaks).

Go to `about:config` page in your browser and set following settings:
`browser.sessionstore.resume_from_crash false` to disable saving session information
`browser.cache.disk.enable false` disable disk cache
`browser.cache.memory.enable true` to turn memory cache instead
`browser.cache.memory.capacity` set memory capacity to desired value, or -1 to disable

