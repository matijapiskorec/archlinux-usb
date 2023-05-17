# Install and setup audio on Arch Linux

Install alsa and pulseaudio (alsa alone should work but not with me):
```
sudo pacman -S alsa-utils pulseaudio
reboot
```

Add yourself to audio group:
```
sudo gpasswd -a matija audio
```

Run alsamixer to set volume:
```
alsamixer
```

Install cmus music player and optional dependency for mp3 playback:
```
sudo pacman -S cmus
sudo pacman -S --asdeps libmaid
```

For other optional dependencies for cmus run:
```
sudo pacman -Si cmus
```

For cmus tutorial run:
```
man cmus-tutorial
```

Basic cmus commands...
Cycle through menus (playlist, library): `[1-7]`
Add folder to library (in menu 5): `a`
Refresh library after folder contents changed (in menu 2): `u`
Play/Restart: `x`
Pause/Play: `c`
Stop: `v`

## Troubleshooting

Sometimes sound from the speakers dies while headphones continue to work fine. In that case you have too:
```
pusleaudio --kill
rm -r .config/pulse
```

Reboot and the sound from the speakers should return.

## Testing microphone

The simplest way to test is your microphone working is by running: `arecord -vv -f dat /dev/null`
Recording audio from your microphone for 5 seconds: `arecord -d 5 test.wav`
Playing recorded audio from your microphone: `aplay test.way`

To setup microphone volume, I found that the best results with the laptop's integrated microphones are by running `alsamixer` and then set Mic Boost and Internal Mic Boost values to half-way.

## Setting your default sound card

Instruction from the official Alsa project webpage. Find your desired card with:
```
cat /proc/asound/cards
```

and then create `/etc/asound.conf` with following:
```
defaults.pcm.card 1
defaults.ctl.card 1
```

Replace "1" with number of your card determined above.

## pulsemixer

You can use pulsemixer instead of alsamixer. Install it:
```
sudo pacman -Syu pulsemixer
```

And run it with:
```
pulsemixer
```

List sources and sinks:
```
pulsemixer --list
```

## Migrating my Arch Linux installation from Thinkpad X220 to Thnikpad X13

After I migrated my Arch Linux installation from Thinkpad X220 to Thinkpad X13 (in March/April 2023) the sound and local video reproduction was broken. Youtube videos in Firefox are working, but local video reproduction in mpv and other programs freezes, with sound sometimes playing and sometimes not.

At first I thought that problems with video and sound playback on my new Thinkpad X13 in January 2023 might be related to the problems with Pulseaudio and Pipewire:
<https://archlinux.org/news/undone-replacement-of-pipewire-media-session-with-wireplumber/>

So I tried to replace PulseAudio with Pipewire:
```
sudo pacman -Sy pipewire-pulse
sudo pacman -Sy pipewire-alsa
sudo pacman -Sy pipewire-jack
```

PipeWire on Arch Linux
<https://wiki.archlinux.org/title/PipeWire>

    Install pipewire-pulse. It will replace pulseaudio and pulseaudio-bluetooth. Reboot, re-login or stop pulseaudio.service and start the pipewire-pulse.service user unit to see the effect.

    Normally, no further action is needed, as the user service pipewire-pulse.socket should be enabled automatically by the package. To check if the replacement is working, run the following command and see the output: 

Installing SOF Firmware, as per this suggestion:
<https://bbs.archlinux.org/viewtopic.php?id=266000>

```
sudo pacman -Sy sof-firmware
```

I can see my audio card on Thinkpad X13:
```
lspci -vvv
```

However, the output of `cat /proc/asound/cards` shows no sound cards!

After updating the whole system with `sudo pacman -Syu` the Youtube videos in Firefox and audio files in mpv work now! But local videos still don't work through mpv as well as any application that uses camera - MD Teams, Discord, even Elements (which is purely text based chat).

I can now see sound cards as well:

    > cat /proc/asound/cards
     0 [sofhdadsp      ]: sof-hda-dsp - sof-hda-dsp
                          LENOVO-21BNS0CS00-ThinkPadX13Gen3

Arch Linux pages for Thinkpad X13 mentions no sound issues:
<https://wiki.archlinux.org/title/Lenovo_ThinkPad_X13_Gen_1_(AMD)>
<https://wiki.archlinux.org/title/Lenovo_ThinkPad_X13_Gen_2_(AMD)>
<https://wiki.archlinux.org/title/Lenovo_ThinkPad_X13_Yoga_(Gen_2)>

It is indicated that with kernel 6+ there is no more problems with webcam. My Linux LTS is currently in 5.15 while standard kernel is in 6.1. See note `linux-lts.md` on how to switch kernels. I tried to switch kernels and this didn't solve my problem!

Hardware video acceleration
<https://wiki.archlinux.org/title/Hardware_video_acceleration>

    mpv with its command-line support is great for testing hardware acceleration. Look at the log of mpv --hwdec=auto video_filename and see hwdec for more details.
    For Intel GPU, use intel-gpu-tools and run intel_gpu_top as root to monitor the GPU activity during video playback for example. The video bar being above 0% indicates GPU video decoder/encoder usage.

Installing wireplumber instead of pipewire-media-session:
```
sudo pacman -Syu wireplumber
```

Now audio works in local videos but their image is still frozen!

I also used pactl to list my audio sinks:
```
pactl info
```

I tried installing `intel-ucode` which is equivalent to Ubuntu `intel-microcode` - it is present in Ubuntu system which is installed on Thinkpad X13 (which I intend to wipe out) but not in my Arch system!

Microcode
<https://wiki.archlinux.org/title/Microcode>

grub-mkconfig will automatically detect the microcode update and configure GRUB appropriately. After installing the microcode package, regenerate the GRUB configuration to activate loading the microcode update by running:
```
grub-mkconfig -o /boot/grub/grub.cfg
```

Still nothing:-( In general the sound doesnt't work anymore - this was even before the Microcode update I did above. Will try with linux kernel instead of linux-lts.

The sound now works if I unmute the speaker and headphones with alsamixer - I did it previously and it didn't work! Could this be problem with the kernel? I'm now running linux kernel. Will test this when I go back to linux-lts. 

The problem is that I doesn't automatically switch between headphone and speaker when I unlug the headphones:-( The sound on local videos works but they are still frozen!

I tried linux-lts and everthing works as in linux! So kernel is not the issue!

It seems that intel-media-driver on Arch is equivalent to intel-va-media-driver on Ubuntu:
<https://packages.ubuntu.com/lunar/intel-media-va-driver> VAAPI driver for the Intel GEN8+ Graphics family
<https://archlinux.org/packages/community/x86_64/intel-media-driver/> Intel Media Driver for VAAPI — Broadwell+ iGPUs

SOLUTION: Long story short, I think that the only problem was in `xf86-video-intel` Intel driver which I removed later. The issues were compounded by my attempt to replace Pulseaudio with Pipewire, which I'm not sure whether it solved anything. In the end I reverted back to Pulseaudio and removed the Intel driver.

Replacing PulseAudio with Pipewire:
<https://www.guyrutenberg.com/2021/03/11/replacing-pulseaudio-with-pipewire/>

Check your running PipeWire services with:
```
systemctl --user status pipewire\*
```

Together with Wireplumber:
```
systemctl --user status \*wire\*
```

<https://www.reddit.com/r/archlinux/comments/l82u3y/pipewire/>

    thanks for the quick reply. I believe found the issue. There was an old pipewire config file: /etc/pipewire/pipewire.conf that was in conflict with the version pacman wanted to install. So replacing pipewire.conf with pipewire.conf.pacnew and restarting pipewire and pipewire-pulse solved the problem.

<https://forum.endeavouros.com/t/sound-broken-with-latest-pipewire-update-1-0-3-24-1/12853/4>

    Replace /etc/pipewire/media-session.d/media-session.conf with /etc/pipewire/media-session.d/media-session.conf.pacnew if you have it in the directory. If not, nuke the whole /etc/pipewire folder and reinstall pipewire (and all the dependencies)

<https://www.reddit.com/r/archlinux/comments/m7yc6j/pipewire_0324_no_audio_devices_found/>

    Remove all the configuration files in /etc/pipewire (sudo mv /etc/pipewire /tmp)

    Reinstall pipewire, pipewire-pulse, and pipewire-media-session (sudo pacman -S pipewire pipewire-pulse pipewire-media-session)

    Enable and start the relevant services (systemctl --user enable pipewire pipewire-pulse pipewire-media-session) and (systemctl --user restart pipewire pipewire-pulse pipewire-media-session). After that, my devices appeared as usual and I was back in business.

    Instead of doing both systemctl --user enable and systemctl --user restart, you can do systemctl --user enable --now which will both enable and start (not sure about restart, actually) the service.

pipewire-pusle.service reports something about xdg-desktop-portal not being installed. I already have xdg-utils, I don't know whether this error is relevant at all.
```
systemctl --user status \*wire\*
```

    ● pipewire-pulse.service - PipeWire PulseAudio
         Loaded: loaded (/usr/lib/systemd/user/pipewire-pulse.service; disabled; preset: enabled)
         Active: active (running) since Sun 2023-02-05 13:05:52 CET; 37min ago
    TriggeredBy: ● pipewire-pulse.socket
       Main PID: 2012 (pipewire-pulse)
          Tasks: 2 (limit: 18790)
         Memory: 21.5M
            CPU: 1.592s
         CGroup: /user.slice/user-1000.slice/user@1000.service/session.slice/pipewire-pulse.service
                 └─2012 /usr/bin/pipewire-pulse

    Feb 05 13:05:52 arch systemd[811]: Started PipeWire PulseAudio.
    Feb 05 13:05:52 arch pipewire-pulse[2012]: mod.rt: Can't find org.freedesktop.portal.Desktop. Is xdg-desktop-portal running?
    Feb 05 13:05:52 arch pipewire-pulse[2012]: mod.rt: found session bus but no portal
    Feb 05 13:05:53 arch pipewire-pulse[2012]: mod.protocol-pulse: client 0x5587a48e5550 [mpv]: ERROR command:-1 (invalid) tag:2 error:25 (Input/output error)
    Feb 05 13:05:53 arch pipewire-pulse[2012]: mod.protocol-pulse: client 0x5587a48e5550 [mpv]: ERROR command:-1 (invalid) tag:2 error:25 (Input/output error)

It seems that pipewire-pulse-service is not enabled? I enabled it with:
```
systemctl --user enable --now pipewire pipewire-pulse
```

Now it is enabled but I don't think this makes any difference.

When I search for mpv in journalctl entries I get this error on boot (not when I start mpv with video where sound works but video itself is frozen).
```
sudo journalctl | grep mpv
```

    Feb 05 13:46:15 arch pipewire-pulse[2208]: mod.protocol-pulse: client 0x558ae9eb8550 [mpv]: ERROR command:-1 (invalid) tag:2 error:25 (Input/output error)

This is the post which mentions exactly this error:

Videos don't play with an unavailable audio sink
<https://gitlab.freedesktop.org/pipewire/pipewire/-/issues/1951>

This mpv error doesn't appear on my Thinkpad X220 laptop (xdg-desktop-portal problem is still present so I would say that this is not problematic):

    ● pipewire-pulse.service - PipeWire PulseAudio
         Loaded: loaded (/usr/lib/systemd/user/pipewire-pulse.service; enabled; preset: enabled)
         Active: active (running) since Sun 2023-02-05 14:29:56 CET; 1min 39s ago
    TriggeredBy: ● pipewire-pulse.socket
       Main PID: 688 (pipewire-pulse)
          Tasks: 2 (limit: 9345)
         Memory: 2.5M
            CPU: 23ms
         CGroup: /user.slice/user-1000.slice/user@1000.service/session.slice/pipewire-pulse.service
                 └─688 /usr/bin/pipewire-pulse

    Feb 05 14:29:56 arch systemd[677]: Started PipeWire PulseAudio.
    Feb 05 14:29:56 arch pipewire-pulse[688]: mod.rt: Can't find org.freedesktop.portal.Desktop. Is xdg-desktop-portal running?
    Feb 05 14:29:56 arch pipewire-pulse[688]: mod.rt: found session bus but no portal

Trying again after a while... (8.4.2023.)
```
fuser -v /dev/snd/*
```

<https://forum.manjaro.org/t/testing-update-2022-10-10-pipewire-haskell-python-firefox-thunderbird-glibc/123842/4>

    Update: I figured out what the problem was (spoiler, I messed something up). I had previously switched to pipewire, only to return to pulseaudio after running into issues (back in July, I think). I apparently still had wireplumber and pipewire-alsa installed from that, and with the recent update they were taking over audio devices before pulseaudio could (pipewire likely received optimizations to start faster).

    On a computer that did not have the issue, all devices were controlled by pulseaudio

    To clean that up, I ran the following:

    sudo pacman -Rdd pipewire-alsa
    sudo pacman -Rnsc wireplumber
    sudo pacman -S pulseaudio-alsa manjaro-alsa

Video playback not working in all browsers and all players
<https://forum.garudalinux.org/t/video-playback-not-working-in-all-browsers-and-all-players/14085>

    I posted this fix today for broken sound/youtube, etc. See if it works for you.... Remove all the configuration files in /etc/pipewire (sudo mv /etc/pipewire /tmp) Reinstall pipewire, pipewire-pulse, and pipewire-media-session (sudo pacman -S pipewire pipewire-pulse pipewire-media-session) Enable …

Online videos sometimes only play first frame and video freezes
<https://forum.manjaro.org/t/online-videos-sometimes-only-play-first-frame-and-video-freezes/102257>
```
pacman -Qs 'pulse|pipewire|wireplumber'
```

It seems that properly removing pipewire and reinstalling pulseaudio at least restores the browser videos, and return the local sound, although local videos are still frozen.
```
sudo pacman -S pulseaudio
sudo pacman -S jack2
sudo pacman -S pulseaudio-alsa
sudo pacman -Rdd pipewire-alsa
sudo pacman -R pipewire-jack
sudo pacman -R wireplumber pipewire-audio libpipewire libwireplumber
sudo pacman -Syu pipewire-media-session
```

Running just this command will not work because there are too many dependencies, so follow the order above. Also, you will not be able to remove pipewire!
```
sudo pacman -R pipewire pipewire-alsa pipewire-jack pipewire-audio wireplumber
```

The enable and stop the appropriate services:
```
systemctl --user enable --now pulseaudio.service
systemctl --user enable --now pulseaudio.socket
systemctl --user stop --now pipewire-pulse.service
systemctl --user stop --now pipewire-pulse.socket
systemctl --user stop --now pipewire.socket
```

Actually, these pipewire services should be disabled!
Will try to reboot and change kernel back to LTS!

Check that pipewire services are indeed not running anymore and pulse is running:
```
systemctl --user status \*wire\*
systemctl --user status \*pulse\*
```

On my pipewire Arch Linux laptop X220:
```
> fuser -v /dev/snd/*
                     USER        PID ACCESS COMMAND
/dev/snd/controlC0:  matija      628 F.... wireplumber
/dev/snd/seq:        matija      627 F.... pipewire
```

On my pulseaudio Arch Linux USB installation which is running on X13:
```
> fuser -v /dev/snd/*
                     USER        PID ACCESS COMMAND
/dev/snd/controlC0:  matija    15074 F.... pulseaudio
/dev/snd/seq:        matija    18611 F.... alsamixer
```

On the same X13 but running Ubuntu and pulseaudio:
```
> fuser -v /dev/snd/*
                     USER        PID ACCESS COMMAND
/dev/snd/controlC0:  matija     2004 F.... pulseaudio
```

This eventually solved the problem!
```
sudo pacman -R xf86-video-intel
```

Intel graphics
<https://wiki.archlinux.org/title/Intel_graphics>

    Note: Some (Debian & Ubuntu, Fedora, KDE) recommend not installing the xf86-video-intel driver, and instead falling back on the modesetting driver for Gen 4 and newer hardware. See [1], [2], Xorg#Installation, and modesetting(4). However, the modesetting driver can cause problems such as screen tearing and mouse jittering on XFCE, artifacts when switching virtual desktops in Chromium, and vsync jitter/video stutter in mpv

[solved] GPU Intel driver problem
<https://bbs.archlinux.org/viewtopic.php?id=283950>

    xf86-video-intel has not been actively maintained for 10 years it should not be used unless you have a system from that timeframe, the focus is on the modesetting driver/wayland.

Also, make sure you have sof-firmware installed:

[SOLVED] Audio not working, soundcard not detected
<https://bbs.archlinux.org/viewtopic.php?id=253051>

rollback pipewire to PulseAudio
<https://unix.stackexchange.com/questions/672788/rollback-pipewire-to-pulseaudio>

    What helped me was doing:

    systemctl --user disable pipewire pipewire.socket
    systemctl --user mask pipewire pipewire.socket

