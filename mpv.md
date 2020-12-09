# mpv video player

Install mpv video player:
```
sudo pacman -Syu mpv
```

You can play a movie with:
```
mpv [PATH TO MOVIE]
```

You can also stream a Youtube video with:
```
mpv [URL OF YOUTUBE VIDEO]
```

If you want just audio:
```
mpv --video=no [URL OF YOUTUBE VIDEO]
```

For subtitles, make sure your subtitle filename matches exactly the filename of the video file you are playing!

## Shortcuts

Delay subtitle in positive/negative direction by 100 ms increments: `x/z`

## My i3/tmux setup to play youtube videos

I usually create a tmux session for youtube:
```
tmux new -s youtube
```

Then split it up horizontally in tmux so that I have mpv controls in the upper screen and a lower screen where I fire up alsamixer. When video starts playing I can detach the youtube tmux session and the video will continue playing.

Then I usually toggle floating property on the mpv window playing the youtube video: `$mod Shift Space`
And then resize it so that it is centered in the middle of the screen: `$mod r`

## Delay/shift subtitles

mpv has key shortcuts for delaying subtitles!
Increase subtitle delay: `z`
Decrease subtitle delay: `x`

You can use this script in Bash to shift subtitles of your srt files in command line:
<https://github.com/helixarch/subedit>

Once you find out your delay just run the subedit script (replaces file in place!), for example to delay it for the -4600 ms (you can also do positive delay):
```
subedit -i subtitle.srt -s -00:00:04,600
```

Help with examples:
```
subedit -H
```

