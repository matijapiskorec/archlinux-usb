# Sending data over network with netcat

Install netcat, OpenBSD version (there is also GNU version gnu-netcat but it is not well maintained and does not support IPv6):
```
sudo pacman -Syu openbsd-netcat
```

Video streaming over local network using netcat:
<https://unix.stackexchange.com/questions/79103/stream-video-using-netcat-and-vlc>

On the server:
```
cat mymovie.mp4 | netcat -l -p 8111
```

On the client:
```
netcat 192.168.1.116 8111 | mpv -
```

Can you stream from a laptop camera? :-D

Can you make a video call by streaming from two cameras at the same time?

Sending large files...

Sender:
```
tar cf - * | netcat 192.168.1.116 7000
```

Receiver:
```
netcat -l -p 7000 | tar x
```

Create and stream a tar archive of your whole home and var directories from a remote host, without explicitly storing it into disk first:
```
ssh 192.168.1.116 "tar zcflpP - /home /var" | pv > backup.tar.gz
```

pv is for progress!

