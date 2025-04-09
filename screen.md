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

If you lost a connection while attached to the screen, screen will stay attached (you can check this with `screen -list`) but on the terminal to which you no more have access. In this case you first need to detach it from the terminal where it is and then attach to it (use one of the bellow):
```
screen -r -d 5241
screen -rd 5241
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

If the screen is already attached you cannot attach again to it (you have to use `-rd` to detach from previous session and attach again). However, you might want to attach multiple times, for whatever reason. In this case your screen will be multiplied - you will see the same screen on two different places! Useful if you have a multiple monitor setup (for example, because you are presenting something on an external monitor) and you want to work on one monitor but show your terminal on another one. In this case you can attach yourself to non-detached screen session with:
```
screen -xr name-of-screen
```

Screen will refuse to attach from within itself. However, sometimes it is possible to make a loop, which are not automatically detected - take care!

Start a new scree session in a detached mode - useful when creating multiple screens in an automated way:
```
screen -dmS name-of-screen
```

You can also create a screen in detached mode with some program running. Your shell is the default. Remember that screen will automaticall exit as soon as the program finishes!
```
screen -dmS name-of-screen
screen -dmS name-of-screen top
```

Send a specific command to the screen session. For example, you might want to quit the screen:
```
screen -S name-of-screen -X quit
```

Or you want to detach a screen:
```
screen -S name-of-screen -X detach
```

Or, you might want to send a string of characters as if typed (don't forget to add `\n` after every command if you want to actually execute the command!):
```
screen -S name-of-screen -X stuff "echo Hello World\n"
screen -S name-of-screen -X stuff "cd\nls -laht\n"
```


