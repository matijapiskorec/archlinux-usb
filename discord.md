# Discord communication server

Install Discord from standard Pacman repository:
```
sudo pacman -Syu discord
```

Run it with:
```
discord
```

In the future, if a new Discord version is available you will have to force the update through Pacman rather than through Discord app. In order to do this without updating your whole system, first update your Pacman repositories,then install an update only for Discord package:
```
sudo pacman -Sy
sudo pacman -S discord
```

