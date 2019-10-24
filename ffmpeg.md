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

Shorten the duration of the audio to 79 minutes:
```
ffmpeg -t 1:19:00 -i input.mp3 input-short.mp3
``` 

## Rip the DVD video

Mount the DVD to `/mnt/` directory:
```
sudo mount /dev/sr0 /mnt/
```

Combine all the video files into one which will be stored locally:
```
cat /mnt/VIDE_TS/*.VOB > ~/media/rom/output.vob
```

Analyze deep buried streams:
```
ffmpeg -analyzeduration 100M -probesize 100M -i ~/media/rom/output.vob
```

Convert it to .mkv file:
```
ffmpeg \
  -analyzeduration 100M -probesize 100M \
  -i ~/media/rom/jezeva-kuca/jezeva-kuca.vob \
  -map 0:1 -map 0:4 -map 0:5 -map 0:6 \
  -metadata:s:a:0 language=hrv -metadata:s:a:0 title="Croatian stereo" \
  -metadata:s:a:1 language=eng -metadata:s:a:1 title="English stereo" \
  -metadata:s:a:2 language=fra -metadata:s:a:2 title="French stereo" \
  -codec:v libx264 -crf 21 \
  -codec:a libmp3lame -qscale:a 2 \
  ~/media/rom/jezeva-kuca/jezeva-kuca-ffmpeg.mkv
```

Map streams 0:1 (video) and three audio streams 0:4, 0:5 and 0:6, discard the subtitles. As for the quality, we have chosen 21 (51 is the worst quality, 0 is lossless).

Although, probably the easiest way is to use vlc media player's convert features to rip DVD directly to mp4 with default settings.
