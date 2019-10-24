# Password management with pass

Simple password management with [pass](https://www.passwordstore.org/). Install pass:
```
sudo pacman -Syu pass
```

Initialize the password store:
```
pass init <gpg-id or email>
```

You can use your standard gpg key or create a new one just for this.

To add a new password for username `user@service.com` on service `service.com`:
```
pass insert service.com/user@service.com
```

To view password store run:
```
pass
```

Or, if you have dmenu installed:
```
passmenu
```

To retrieve a password run:
```
pass service.com/user@service.com
```

Or, if you want to copy the password to clipboard with xclip:
```
pass -c service.com/user@service.com
```

The password clears from clipboard after 45 seconds, although it may linger longer if you use a clipboard manager such as clipmenu! To clear all entries in clipmenu run:
```
clipdel -d ".*"
```

To generate a new random password of length 8 for a particular service (argument `-n` is to generate a password without symbols!) run:
```
pass -n generate service.com/user@service.com 8
```

You can edit a password in your default text editor:
```
pass edit service.com/user@service.com
```

You can additionally initialize a password store as a git repozitory, which will automatically make a commit each time you generate a new password:
```
pass git init
```

