# Manage multiple monitors with xrandr

Install `xorg-xrandr` package for managing displays:
```
sudo pacman -Syu xorg-xrandr
```

Check status of currently available displays:
```
xrandr
```

Switch monitor `DVI-I-2` to be left of `DVI-I-1`:
```
xrandr --output DVI-I-2 --left-of DVI-I-1
```

Connect to the external VGA display:
```
xrandr --output VGA1 --auto
```

Disconnect from the external VGA display:
```
xrandr --output VGA1 --off
```

Adjust brightness of a display:
```
xrandr --output LVDS1 --brightness 0.8
```

# Configuration for Thinkpad x220 with Full HD display using Nitrocaster's mod

I have Thinkpad x220 with Full HD display using Nitrocaster's mod. Display is connected to DP3, but primary LVDS1 is still connected and active, although it does not exist anymore. The brightness keys do not work at all. One suggeston was to duplicate displays, probably with something like:
```
xrandr --output DP3 --same-as LVDS1
```

But this does not work in my case. So I have to adjust brightness manually:
```
xrandr --output DP3 --brightness 0.8
```

Also, connecting the the external VGA display will not work automatically unless you first disconnect the dummy LVDS1 display. Run:
```
xrandr --output LVDS1 --off
xrandr --output VGA1 --auto
```

And then optionally:
```
xrandr --output VGA1 --left-of DP3
```

## Connecting to HDMI output

To connect to the external HDMI output (check the exact name of your HDMI output with `xrandr`):
```
xrandr --output HDMI1 --auto
```

Your screen will be duplicated. You mihgt need to adjust volume control, as the audio will probably stay only on your laptop. The easiest way to do this is through pavucontrol:
```
sudo pacman -S pavucontrol
```

Now you can run pavucontrol, go to Configuration and change the Built-in Audio to Digital Stereo (HDMI) output. You can also do it through command line (examples for changing to HDMI and back to analog output):
```
pactl set-card-profile 0 output:hdmi-stereo
pactl set-card-profile 0 output:analog-stereo
```

To switch off HDMI output just run:
```
xrandr --output HDMI1 --off
```


