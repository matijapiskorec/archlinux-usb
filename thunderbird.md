# Thunderbird email client

Install Thunderbird through Pacman:
```
sudo pacman -Syu thunderbird
```

## Configuration

Turn off annoying notifications in Thunderbird. Go to `Preferences`, `Advanced`, `Config Editor`. Search for options `mail.biff.show_alert` and `mail.biff.use_system_alert` and set them to false.

To set up mail threading, so that email are grouped by threads which can be collapsed or expanded, first make sure that the appropriate email account is selected. Then click on the menu to the far right `Thunderbird Menu`, then `View`, then `Sort by` then choose `Threaded` from the menu.

## Thunderbird command line interface

You can compose Thunderbird email from command line, for example:
```
thunderbird -compose "subject='test',to='test@mail.test',body=$output,attachment='/home/test/scan.log'"
```

Thunderbird compose window will open and you just have to click Send. There is no automatic way of sending emails through Thundebird CLI interface!

## End-to-end encryption in Thunderbird

Introduction to End-to-end encryption in Thunderbird
<https://support.mozilla.org/en-US/kb/introduction-to-e2e-encryption>

OpenPGP in Thunderbird - HOWTO and FAQ
<https://support.mozilla.org/en-US/kb/openpgp-thunderbird-howto-and-faq>

## Webcal Calendar

Import webcal calendar through link (they begin with `webcal://`). Go to calendar, right click `New Calendar` and then `On the network`, choose `iCalendar (ICS)` and paste yout webcal link in the `Location` box. The new calendar should be created and you can view it. You have to associate the calendar with one of your emails.

If the link does not work you can try to replace `webcal://` with `http://` or  `https://`.

## SOGo calendar

SOGo is an open source groupware and calendar server:
<https://www.sogo.nu/>

To setup SOGo calendar in Thunderbird you don't need any special plugin in new versions of Thuderbird. Just add a new network-based calendar, enter CalDAV URL which is provided in SOGo, enter your username (usually email) and choose appropriate settings.

## Problems with sending Microsoft emails over Thunderbird

Setting up Office365 (Outlook/Microsoft) email over Thunderbird usually works smoothly - you just enter your email address and password while adding account and everything works. However, with one of the accounts (I have multiple Microsoft email accounts in Thunderbird) I could receive but not send emails! The settings were correct but the admin on the email server had to setup following settings for my user:

    Authenticated SMTP - treba biti uključena
    Manage MFA - treba biti isključena

## Problem with Thunderbird prompting for too many passwords

Thunderbird version 102.7 has problem with Office365 and Microsoft accounts, resulting in asking for too many passwords:

Important: Thunderbird 102.7.0 And Microsoft 365 Enterprise Users
<https://blog.thunderbird.net/2023/01/important-message-for-microsoft-office-365-enterprise-users/>

As a temporary workaround you can downgrade the Thunderbird until issue is resolved in late January 2023. I downgraded to 102.4 which is the latest version in my Pacman cache:
```
sudo pacman -U file:///var/cache/pacman/pkg/thunderbird-102.4.1-1-x86_64.pkg.tar.zst
```

I also added thunderbird to the list of ignored packages until this issue is resolved:
```
sudo vim /etc/pacman.conf
```

Added this option:
```
[options]
# Pacman won't upgrade packages listed in IgnorePkg and members of IgnoreGroup
IgnorePkg   = thunderbird
```

