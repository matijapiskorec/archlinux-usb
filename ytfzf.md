# Simple Youtube viewer for the terminal

ytfzf is a simple one-line posix script to browse Youtube from the terminal. You can find it:
<https://github.com/pystardust/ytfzf>

Install it in the following way:
```
cd ~/src
git clone https://github.com/pystardust/ytfzf
chmod +x ytfzf/ytfzf
cp ytfzf/ytfzf ~/bin/
```

It needs ueberzug to show thumbnails in the terminal, you can install it from Arch repositories:
```
sudo pacman -Syu ueberzug
```

I already had some version which I installed through pip3, but I could not locate it with `pip3 freeze` so I'm not completelly sure (see notes for vifm, I tried to install it there for image preview). Anyway, I could not install it through pacman until I got rid of the old version in `/usr/bin`, so I renamed it to backup first:
```
sudo cp /usr/bin/ueberzug /usr/bin/ueberzub-backup
```

This is a simple Python script anyway. So now I was able to install it with Pacman.

Problem is that thumbnails still do not work in st terminal, only in urxvt:-(

## Reference

Help: `ytfzf -h`
Audio only: `ytfzf -m`
Download to current directory: `ytfzf -d`
Loop, prompt selector again after video ends: `ytfzf -l`
After the video ends make another search: `ytfzf -s`

A similar alternative is lf-yt (I think it needs Youtube API key while ytfzf does not need it):
<https://github.com/pystardust/ytfzf>

