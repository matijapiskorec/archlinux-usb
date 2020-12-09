# Remote desktop in Arch Linux

Install FreeRDP - a remote desktop protocol implementation that supports connecting to Windows machines as well. Install it through pacman:
```
sudo pacman -Syu freerdp
```

Now you can connect to a Windows machine:
```
xfreerdp /u:username /v:server.com
```

