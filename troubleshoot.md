# Troubleshooting problems in Arch Linux

Some general advice, along with concrete use cases, of how to troubleshoot when something goes wrong and how to fix it.

## Slow boot time

You experience slow boot times or suspect something is stalling the boot process. First inspect systemctl logs to see if there is a service that has unusually long init time or failed to load properly:
```
systemctl --all
systemd-analyze blame
```

Then inspect journal to see the whole boot log trace:
```
sudo journalctl -b
```

If there is a potentially problematic service you can stop or disable it (so it does not run at startup) with:
```
systemctl --user disable [SERVICE]
systemctl --user stop [SERVICE]
```

The `--user` flag is for services that run in user space, it should be ommited for services that run in kernel space (in that case it will also prompt you for a sudo password).

A concrete use case is when the the crng init service stalled the whole system, which was especially noticable right after the login. The offending entry in the journalctl log was this:
```
Feb 10 19:15:10 arch login[357]: LOGIN ON tty1 BY user
Feb 10 19:15:47 arch kernel: random: crng init done
```

Which indicated a 37 second lag for the crng init. This was not so easy to notice because the entry was buried among entries from other services, some of which experienced errors of their own because of the prolonged startup (as some variables were not properly set). What made things worse, an exactly the same Arch Linux installation (through live USB drive) didn't exhibit any problems on three other computers. This concrete problem was due to a bug in Linux kernel described [here](https://unix.stackexchange.com/questions/442698/when-i-log-in-it-hangs-until-crng-init-done). The solution was to install [rngd-tools](https://wiki.archlinux.org/index.php/Rng-tools) package which manages random number generation in kernel, and enabling it as a service:
```
sudo pacman -Syu rngd-tools
sudo systemctl enable rngd.service
sudo systemctl start rngd.service
```
