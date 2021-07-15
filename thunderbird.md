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

## Calendar

Import webcal calendar through link (they begin with `webcal://`). Go to calendar, right click `New Calendar` and then `On the network`, choose `iCalendar (ICS)` and paste yout webcal link in the `Location` box. The new calendar should be created and you can view it. You have to associate the calendar with one of your emails.

If the link does not work you can try to replace `webcal://` with `http://` or  `https://`.

