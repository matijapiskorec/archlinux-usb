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

If Firefox takes too much memory you can try to do manual garbage collection. Go to `about:memory` and try to free memory with the options provided there. You can also measure memory consumption if you suspect that there is a web page which uses too much memory.

## Hardware acceleration

Sometimes hardware acceleration can cause strange horizontal streaks when scrolling. To disable it go to `Preferences` and then uncheck first `Use recommended performance settings` and then `Use hardware acceleration when available`.

## Setting as the default browser

You can set Firefox as the default browser from within the Preferences. It should work for Syncthing and Jupyter at least.
