# Download Youtube and other videos with youtube-dl

Install youtube-dl:
```
sudo pacman -Syu youtube-dl
```

List all available formats for the video:
```
youtube-dl -F "https://www.youtube.com/watch?v=WXuK6gekU1Y"
```

Download just audio from a Youtube video in mp3 format:
```
youtube-dl -x --audio-format mp3 https://www.youtube.com/watch?v=ZAYZmIfHEiU
```

Download video in mp4 format along with the subtitles:
```
youtube-dl -f mp4 --write-sub "https://www.youtube.com/watch?v=WXuK6gekU1Y"
```

If you listed all available formats with `-F` first, you can simply use the code in the `-f` flag. For example, here I donwload a video in the highest quality in mp4 format, along with the subtitles which I then convert to srt:
```
youtube-dl -f 137 --write-sub --convert-subs srt "https://www.youtube.com/watch?v=WXuK6gekU1Y"
```

Be carefull because many of the video formats in that list are labaled as video-only, meaning you won't get any audio! For this you can select both video and audio formats by using `-f video+audio` option. The best way for this, if you want to select the best version of a specific format, is the following:
```
youtube-dl -f 'bestvideo[ext=mp4]+bestaudio[ext=m4a]' "https://www.youtube.com/watch?v=WXuK6gekU1Y"
```

The output video will be automatically merged and the original files will be deleted. If you want to keep them you can use `-k` option.

If none of the formats suits you, you can recode a video in another format with `--recode-video` option.

