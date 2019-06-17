# Install and setup audio on Arch Linux

Install alsa and pulseaudio (alsa alone should work but not with me):
```
sudo pacman -S alsa-utils pulseaudio
reboot
```

Add yourself to audio group:
```
sudo gpasswd -a matija audio
```

Run alsamixer to set volume:
```
alsamixer
```

Install cmus music player and optional dependency for mp3 playback:
```
sudo pacman -S cmus
sudo pacman -S --asdeps libmaid
```

For other optional dependencies for cmus run:
```
sudo pacman -Si cmus
```

For cmus tutorial run:
```
man cmus-tutorial
```

Basic cmus commands...
Cycle through menus (playlist, library): `[1-7]`
Add folder to library (in menu 5): `a`
Refresh library after folder contents changed (in menu 2): `u`
Play/Restart: `x`
Pause/Play: `c`
Stop: `v`

## Troubleshooting

Sometimes sound from the speakers dies while headphones continue to work fine. In that case you have too:
```
pusleaudio --kill
rm -r .config/pulse
```

Reboot and the sound from the speakers should return.
