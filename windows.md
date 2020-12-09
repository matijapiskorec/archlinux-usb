# Windows hacks

Following are some Windows hacks and tips, mostly related to the interface between Linux and Windows.

## USB memory formating

Sometimes USB memory which is perfectly fine and visible from my Arch Linux machine is not recognized in Windows at all (in this case Windows 7). Here are some tips for making it work. Note that the steps bellow will delete everything from the disk!

Press `Win+R` to open Run window, then type `diskmgmt.msc` to run the Disk Management utility.

Your USB disk should be at least visible in the menu. You can change its drive volume, format it and such. If you can see the drive but cannot format it in the utility you can use command line utility diskpart.

Open command prompt (again, `Win+R` and type `cmd`), then run `diskpart` and give it Administrator privileges. Here are some common commands:

List available disks: `disk list`
Select a disk with number 1: `select disk n`
Clean the selected disk: `clean`

At some point I was able to format it from the Disk Management utility and the USB worked fine in both Windows and my Arch Linux machine.

