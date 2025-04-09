# Networking in Arch Linux

This is a separate guide for some common networking issues.

## netctl

Check your stored wifi passwords, where WLAN-NAME is your wifi network name:
```
sudo cat /etc/netctl/WLAN_NAME
```

If you want to obfuscate your wireless password follow the instructions in the official Arch Linux documentation for netctl:
<https://wiki.archlinux.org/index.php/netctl>

## Reverse DNS lookup

Install bind package from official Arch repository:
```
sudo pacman -Syu bind
```

Now you can to a reverse DNS lookup (find a domain name by using an IP address) with `nslookup`, for example like this:
```
nslookup 8.8.8.8
```

## DNS lookup

You can check an IP address of a domain name with following commands:
```
ping aldaily.com
host aldaily.com
dig aldaily.com
nslookup aldaily.com
```

## NetworkManager

Install `networkmanager` and `nm-connection-editor` for GUI interface:
```
sudo pacman -Syu networkmanager nm-connection-editor
```

Enable the `NetworkManager.service`:
```
sudo systemctl enable --now NetworkManager.service
```

You also get the CLI and ncurses applications `nmcli` and `nmtui`.

Run ncurses interface (similar to wifi-menu):
```
nmtui
```

More information on NetworkManager:
<https://wiki.archlinux.org/title/NetworkManager>

You must ensure that no other service that wants to configure the network is running, as multiple networking services will conflict. This is a generic issue not specific to Network Manager!

So temporarily I disabled the `NetworkManager.service`:
```
sudo systemctl disable --now NetworkManager.service
```

List nearby WiFi networks:
```
nmcli device wifi list
```

Connect to a WiFi network:
```
nmcli device wifi connect SSID_or_BSSID password PASSWORD
```

Activate and deactivate a connection (i.e. connect or disconnect to a network with an existing profile):
```
nmcli connection up name_or_uuid
nmcli connection down name_or_uuid
```

Get a list of connections with their names, UUIDs, types and backing devices:
```
nmcli connection show
```

Get a list of known profiles:
```
nmcli -g NAME connection
```

By default, all profiles are created with autoconnect option set to yes (so after you disconnect from a specific network it will automatically connect to the next available one), but you can disable this for every network individually:
```
nmcli connection modify name_or_uuid autoconnect no
```

Disconnect an interface, for example, disconnect from all WiFi networks (this ignores autoconnect option and it will indeed disconnect from all known networks):
```
nmcli device disconnect wlan0 
```

## NetworkManager applet

You can install an applet for NetworkManager so that connections appear in your system tray - it works with the default i3 system tray as well!
```
sudo pacman -Sy network-manager-applet
```

Then run it with:
```
nm-applet
```

You can add it to your `~/.xinitrc` so that it runs upon startup!

## NetworkManager VPN

You can setup Virtual Private Network (VPN) with NetworkManager using several plugins:
<https://wiki.archlinux.org/title/NetworkManager>

I tried the following:
```
sudo pacman -Sy networkmanager-openconnect
sudo pacman -Sy networkmanager-openvpn
```

However, their command line interfaces are not well documented so I resorted to the vpnc plugin:
```
sudo pacman -Sy networkmanager-vpnc
```

You can now use `np-connection-editor` (I show the installation instructions above) to add a VPN connection:
```
nm-connection-editor
```

Configuration depends on your VPN provider! Once you add a configuration it should be visile in `nmtui` and you should be able to use it as any other network connection.

Still, I had problems connecting to VPN and one of the issues mentioned on the Arch Linux Wiki above is that some of these plugins need `network-manager-applet`, so I installed it and ran it (it shows in my system tray):
```
sudo pacman -Sy network-manager-applet
nm-applet
```

If you have any problems connecting to VPN you can always try to identify the issue by checking the output from journalctl command:
```
journalctl -f
```

This lists all recent journal entries so you should be able to see if there is a problem in NetworkManager.

## Check open ports

You can check open ports on a Linux machine with the following command:
```
nc -z -v localhost 1-65535
```

And you will get a result similar to this:
```
localhost.localdomain [127.0.0.1] 6556 (?) open
localhost.localdomain [127.0.0.1] 2375 (?) open
localhost.localdomain [127.0.0.1] 443 (https) open
localhost.localdomain [127.0.0.1] 111 (sunrpc) open
localhost.localdomain [127.0.0.1] 80 (http) open
localhost.localdomain [127.0.0.1] 25 (smtp) open
localhost.localdomain [127.0.0.1] 22 (ssh) open
```

## speedtest-cli

Install speedtest-cli to test your network speed:
```
sudo pacman -Sy speedtest-cli
```

Now run your speed test:
```
> speedtest
Retrieving speedtest.net configuration...
Testing from XXXXXXXX
Retrieving speedtest.net server list...
Selecting best server based on ping...
Hosted by XXXXX Giganet Internet Kft (Budapest) [298.99 km]: 39.809 ms
Testing download speed................................................................................
Download: 11.17 Mbit/s
Testing upload speed......................................................................................................
Upload: 1.47 Mbit/s
```

## tcpflow

Install tcpflow for TCP network monitoring:
```
sudo pacman -Sy tcpflow
```

The format of the tcpflow filename is:
```
[timestampT]sourceip.sourceport-destip.destport[--VLAN][cNNNN]
```

Yyou can use hexdump command to dump the contents of the log file, for example:
```
hexdump -C 005.022.157.077.18080-010.244.003.016.31768
```

An example of output:

    000017d0  b3 53 e2 5b 00 00 00 00  12 6c 6f 63 61 6c 5f 70  |.S.[.....local_p|
    000017e0  65 65 72 6c 69 73 74 5f  6e 65 77 8c e9 03 0c 03  |eerlist_new.....|
    000017f0  61 64 72 0c 08 04 61 64  64 72 0c 08 04 6d 5f 69  |adr...addr...m_i|
    00001800  70 06 bc 24 07 36 06 6d  5f 70 6f 72 74 07 a0 46  |p..$.6.m_port..F|

You get the raw TCP data (in the right column in ASCII, and the raw hex data in the left columns).


