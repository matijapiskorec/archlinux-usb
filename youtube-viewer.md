# Viewing Youtube videos in command line

Install youtube-viewer:
```
sudo pacman -Syu youtube-viewer
```

Run:
```
youtube-viwer
```

You can immediatelly type in the search term. Once the list of videos appear you can select individual videos or a range of videos to play throug mpv:
```
1 3 5 7-9
```

To run in audio mode:
```
youtube-viewer -n
```

To download videos 3 and 5 to 7:
```
:d3,5-7
```

To run in download mode, where videos are first downloaded in audio mode and stored locally and then the video is played. Videos that already exist are not downloaded!
```
youtube-viewer -n -d --dl-play --wget-dl --downloads-dir=$HOME/music/youtube/
```

Query for a video, select the first one from the list, download it if it does not already exist, play it, and after play prompt user for input (so as to not download and play the next one from the list):
```
youtube-viewer -n -d --dl-play --wget-dl --downloads-dir=$HOME/music/youtube/ --all --confirm Percy Sledge Take Time Know Her
```

