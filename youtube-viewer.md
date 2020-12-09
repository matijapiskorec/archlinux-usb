# Viewing Youtube videos in command line

Install youtube-viewer:
```
sudo pacman -Syu youtube-viewer
```

Run:
```
youtube-viewer
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

## API restrictions

Due to too much users the youtube-dl default API key reached the limit, and so it is recommended that users create their own keys and put it in the `~/.config/youtube-viewer/api.json` file, which allows setting an YouTube API key and the client ID/SECRET values:
```json
{
    "key":           "API_KEY",
    "client_id":     "CLIENT_ID",
    "client_secret": "CLIENT_SECRET"
}
```

As a prerequisite you must create a Google Platform project. Enable the YouTube Data v3 API on your project: [navigate here](https://console.developers.google.com/apis/library/youtube.googleapis.com) and click "Enable" (if you see a blue "Manage" button, it's already enabled). Replace `API_KEY` with your YouTube API key. Create a new key [here](https://console.developers.google.com/apis/credentials) by clicking on "Create Credentials" > "API Key".


