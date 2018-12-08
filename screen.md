# screen terminal multiplexer

Start a new screen (this also immediatelly attaches you to the new screen):
```
screen
```

List available screens:
```
screen -list
```

Once in the screen, you can run a program and if you detach from that screen the program will continue running. Detaching is one with the keyboard shortcut `Ctrl-a d`. You can attach yourself again to the detached screen with `screen -r` command:
```
screen -r
```

If there are multiple screen sessions you will have to choose the one you want to attach. Just write a few first screen id numbers after the `screen -r` command (screen id number is visible with `screen -list`):
```
screen -r 5241
```

If you lost a connection while attached to the screen, screen will stay attached (you can check this with `screen -list`) but on the terminal to which you no more have access. In this case you first need to detach it from the terminal where it is and then attach to it:
```
screen -r -d 5241
```

If you want to terminate screen, just attach yourself to its windows and run `exit` command.
```
exit
```

Name a screen so that it has a name when listing with `screen -list` and to restore it it easier with `screen -r`. When creating a new screen:
```
screen -S name-of-screen
```

Or if you already created it, within screen enter a command mode with `Ctrl-a :` and then enter the command `sessionname name-of-screen`.

Command reference:
Detach from current screen: `Ctrl-a d`
Split the screen vertically into two regions: `Ctrl-a |`
Switch to the next region: `Ctrl-a Tab`
Start a new bash shell in the selected region: `Ctrl-a c`
