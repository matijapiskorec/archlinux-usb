# Silencing beeps in terminal

Silent beep on tab completion, add this line to `/etc/inputrc` or `.inputrc` in home:
```
set bell-style none
```

Silent beeps on less and man listings, add this to `.bashrc`:
```
alias less='less -Q'
alias man='man -P "less -Q"'
```

Silent beeps when using git diff and other git paging commands:
```
git config --global core.pager 'less -q'
```

You can disable PC speaker globally by unloading pcspkr kernel module:
```
rmmod pcspkr
```

Blacklisting the pcspkr module will prevent udev from loading it at boot:
```
echo "blacklist pcspkr" > /etc/modprobe.d/nobeep.conf
```