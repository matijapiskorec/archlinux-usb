# Recording audio and video with ffmpeg

Install ffmpeg:
```
sudo pacman -Syu ffmpeg
```

Check your sound cards:
```
arecord -l
arecord -L
```

Record audio with alsa:
```
ffmpeg -f alsa -i hw:0 -t 5 /tmp/out.wav
```

You can play the audio file with multiple programs:
```
mpv /tmp/out.wav 
vlc /tmp/out.wav 
ffplay /tmp/out.wav 
```

Check video recording devices:
```
v4l2-ctl --list-devices
```

Record video with your available camera:
```
ffmpeg -f v4l2 -framerate 25 -video_size 640x480 -i /dev/video0 /tmp/output.mkv
```

Play the recorded video:
```
mpv /tmp/output.mkv 
```
