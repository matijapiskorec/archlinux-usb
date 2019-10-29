# Setting up Arch Linux with persistent changes on USB key

Original guide for setting up Arch Linux with persistent changes on USB key is here:
https://gitlab.com/c.magyar/archlinux-usb

Html version:
https://valleycat.org/linux/arch-usb.html

Make a bootable Arch live USB in Windows:
https://rufus.akeo.ie/

i3 improved tilling window manager:
https://i3wm.org/docs/

## Guide for the finished system

The Arch Linux installation boots into a basic terminal login, so just type in your username and password to login to the system. i3 tilling window manager is run immediatelly.

To open a terminal window: `Windows-Enter`
To close a terminal window `Windows-Shift-q`
To switch to another workspace: `Windows-Number`
Focus to another window: `Windows-Arrows`
Move a window to another workspace: `Windows-Shift-Number`
Resize a window: `Windows-r` (then use arrows to resize and enter to finish)

Terminal opens a fish shell by default. You can switch to a more standard bash shell by typing `bash` in the terminal. The shell prompts are designed to be visually identical.

Use dmenu as program launcher: `Windows+d`

Connecting to wireless. Run `wifi` from dmenu launcher or from a terminal. It allows you to choose and connect to a wireless network, a master password is needed. This script fetches saved networks from netctl. If you want to add a new wireless network run `wifi-menu` from terminal, connect to a network and then save it as a template.

You can also connect to eduroam network, if avalilable. Run `eduroam-start` and `eduroam-stop` from terminal. Requires master password.

Usefull and commonly used programs which can be run from dmenu...
`firefox` - a web browser
`thunderbird` - email client, retrieves email from several accounts for which master password is needed

