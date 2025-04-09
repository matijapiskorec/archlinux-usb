# Webtorrent - torrents on the web

WebTorrent is the first BitTorrent client in the browser.
<https://webtorrent.io/>

You can use webtorrent-cli as a standalone Node.js command line application.
<https://github.com/webtorrent/webtorrent-cli>

You can install it globally via npm:
```
sudo npm install webtorrent-cli -g
```

Check help with:
```
webtorrent --help
```

You can stream the torrent video directly in mpv player with:
```
webtorrent "magnet:..." --mpv
```

If the video file doesn't include subtitle (typically, mkv files provide them) you have to download them beforehand and load them while starting webtorrent using `--player-args` option, with appropriate subtitle option for your specific player. In mpv, you do it like this:
```
webtorrent "magnet:..." --mpv --player-args="--subfile=/PATH/TO/SUBTITLE"
```

