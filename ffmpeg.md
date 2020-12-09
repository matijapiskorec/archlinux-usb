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

You can record audio directly in mp3 format (hw:1 is my external webcam, while hw:0 is my laptop microphone):
```
ffmpeg -f alsa -i hw:1 ./out.mp3
```

Check video recording devices:
```
v4l2-ctl --list-devices
```

Check available resolutions on your video recording devices:
```
v4l2-ctl --list-formats-ext
```

Record video with your available camera:
```
ffmpeg -f v4l2 -framerate 25 -video_size 640x480 -i /dev/video0 /tmp/output.mkv
```

This is the one I use for my Logitech C920 web camera (the resolution goes up to 1920x1080, but the framerate is lower):
```
ffmpeg -f v4l2 -video_size 640x480 -i /dev/video0 -f alsa -i default -c:v libx264 -preset ultrafast -c:a aac webcam.mp4
```

Play the recorded video (equivalent for the mp4 version):
```
mpv /tmp/output.mkv 
```

Shorten the duration of the audio to 79 minutes:
```
ffmpeg -t 1:19:00 -i input.mp3 input-short.mp3
``` 

Cut the video - copy means that you do not re-encode the video so it should be much faster:
```
ffmpeg -i input.mp4 -ss 00:01:00 -to 00:02:00 -c copy output.mp4
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

## Screen capture with ffmpeg

You can also use recordmydesktop program for screencasting:
```
sudo pacman -Syu recordmydesktop
```

In order to find the id of you window you can use xwininfo:
```
sudo pacman -Syu xorg-xwininfo
```

You can find out the id of the window by running `xwininfo` and clicking on the window. Now you can record your screen:
```
recordmydesktop --windowid 0x18000a9 -o test.ogv
```

An easy way to delay the recording, if you need some time to hide the command window or resize the recorded window to fullscreen, is by using sleep:
```
sleep 3 ; recordmydesktop --windowid 0x18000a9 -o test.ogv
```

To convert this recording to mp4 file format, which yields a much smaller file, run:
```
ffmpeg -i test.ogv \
       -c:v libx264 -preset veryslow -crf 22 \
       -c:a libmp3lame -qscale:a 2 -ac 2 -ar 44100 \
       test.mp4
```

However, the most reliable solution for me is screencast, available in AUR - it uses ffmpeg to record a screen and can output into any format, including mp4. To install it:
```
cd src
git clone https://aur.archlinux.org/screencast.git
cd screencast
makepkg -sri
```

You can now run similary as before (press `q` to stop the recording):
```
sleep 3 ; screencast --size=1920x1080 -1 test.mp4
```

The option `-1` is here to override the default behavior where recording and encoding are done in two steps, with encoding starting only after recording finishes. It turns out that doing both at the same time (`-1` is short for `--one-step`) reduces memory consumption significantly, otherwise a one-minute video takes almost 16 GB of memory which leads to breaking on my system. And there is no additional encoding after the video, so everything is faster. I didn't experience any problems with this one-step process.

All of my screen recordings featured flickering artefacts! It appears it is because of Compton window compositor. I just commented out the line in `.xinitrc` where Compton is started, rebooted the machine (restart of X Server should also be ok) and flickering is gone!
```
# compton -CGb 
```

You can also include webcam overlay, choosing the input, position, size, fps. For the simplest case just use the `-W` option which will use default webcam input `/dev/video0` with resolution 320x240 and position it in the upper right corner:
```
sleep 3 ; screencast --size=1920x1080 -W -1 test.mp4
```

Sometimes you don't want the whole screen but just a single window. First, make sure you have slop installed, as it is used to select a window:
```
sudo pacman -S slop
```

Then run screencast with the `-S` option which lets you either define a region or simply click on a window. Note that in this case you cannot define a screen size!
```
sleep 3 ; screencast -S -W -1 test.mp4
```

If you are using i3 you can configure the size of the window you want to record by first making it floating `Mod+Shift+Space`, then changing the size with `Mod+r`.

If the default webcam window is too large and it takes too much space on your screen capture you can set it to the minimal size:
```
sleep 3 ; screencast -S -W -1 -Z 160x90 test.mp4
```

## Concatenating video files

If you have MP4 files, these could be losslessly concatenated by first transcoding them to MPEG-2 transport streams. With H.264 video and AAC audio, the following can be used:
```
ffmpeg -i input1.mp4 -c copy -bsf:v h264_mp4toannexb -f mpegts intermediate1.ts
ffmpeg -i input2.mp4 -c copy -bsf:v h264_mp4toannexb -f mpegts intermediate2.ts
ffmpeg -i "concat:intermediate1.ts|intermediate2.ts" -c copy -bsf:a aac_adtstoasc output.mp4
```

