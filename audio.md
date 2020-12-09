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

## Testing microphone

The simplest way to test is your microphone working is by running: `arecord -vv -f dat /dev/null`
Recording audio from your microphone for 5 seconds: `arecord -d 5 test.wav`
Playing recorded audio from your microphone: `aplay test.way`

To setup microphone volume, I found that the best results with the laptop's integrated microphones are by running `alsamixer` and then set Mic Boost and Internal Mic Boost values to half-way.

## Setting your default sound card

Instruction from the official Alsa project webpage. Find your desired card with:
```
cat /proc/asound/cards
```

and then create `/etc/asound.conf` with following:
```
defaults.pcm.card 1
defaults.ctl.card 1
```

Replace "1" with number of your card determined above.

## pulsemixer

You can use pulsemixer instead of alsamixer. Install it:
```
sudo pacman -Syu pulsemixer
```

And run it with:
```
pulsemixer
```

List sources and sinks:
```
pulsemixer --list
```

