# Install Popcorn Time for Linux

Download a prebuilt Popcorn Time for Linux:
```
cd ~/Downloads
wget https://get.popcorntime.sh/build/Popcorn-Time-0.3.10-Linux-64.tar.xz
```

Make a directory in `/opt` (usually used for prebuilt packages by third party software distributors, for example Sublime Text), and then extract the archive there:

```
sudo mkdir /opt/popcorntime
sudo tar Jxf Popcorn-Time-* -C /opt/popcorntime
```

Make a symbolic link in `/usr/local/bin` so that you can run it normally as any other program:
```
sudo ln -s /opt/popcorntime/Popcorn-Time /usr/local/bin/popcorntime
```

You can now run PopcornTime from terminal (or by using dmenu):
```
popcorntime
```