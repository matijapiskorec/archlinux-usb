# Configure email on Arch Linux

## Install mutt through the mutt-wizard script

Install dependencies for mutt-wizard:
```
sudo pacman -Syu dialog neomutt offlineimap msmtp
```

Optionally, you can also install notmuch for searching your email (wizard will set it to `Ctrl+f`):
```
sudo pacman -Syu notmuch
```

Clone mutt-wizard script:
```
git clone https://github.com/LukeSmithxyz/mutt-wizard.git ~/.config/mutt
```

Run mutt-wizard script:
```
./mutt-wizard.sh
```

Fetch email with:
```
offlineimap
```

And start neomutt with:
```
neomutt
```

## Configure sup

Unfortunatelly, sup only works with Ruby version 2.3.3. You will have to install it manually as Arch moved to newer versions of Ruby. First, install Ruby Version Manager (RVM). Make sure you have both curl and git installed, then download rvm script:
```
curl -L get.rvm.io > rvm-install
```

Install rvm script:
```
bash < ./rvm-install
```

Put the following in your `.bashrc` to enable rvm in each new terminal session:
```
[[ -s "$HOME/.rvm/scripts/rvm" ]] && source "$HOME/.rvm/scripts/rvm"
```

Install Ruby version 2.3.3, xapian-ruby and sup:
```
rvm install 2.3.3
rvm 2.3.3 do gem install xapian-ruby
rvm 2.3.3 do gem install sup
```

To make sure sup is always run with Ruby version 2.3.3 put the following in your `.bashrc`:
```
alias sup='rvm 2.3.3 do sup'
```

## Thunderbird

Turn off annoying notifications in Thunderbird. Go to `Preferences`, `Advanced`, `Config Editor`. Search for options `mail.biff.show_alert` and `mail.biff.use_system_alert` and set them to false.

To set up mail threading, so that email are grouped by threads which can be collapsed or expanded, first make sure that the appropriate email account is selected. Then click on the menu to the far right `Thunderbird Menu`, then `View`, then `Sort by` then choose `Threaded` from the menu.

## Thunderbird command line interface

You can compose Thunderbird email from command line, for example:
```
thunderbird -compose "subject='test',to='test@mail.test',body=$output,attachment='/home/test/scan.log'"
```

Thunderbird compose window will open and you just have to click Send. There is no automatic way of sending emails through Thundebird cli interface!

## End-to-end encryption in Thunderbird

Introduction to End-to-end encryption in Thunderbird
<https://support.mozilla.org/en-US/kb/introduction-to-e2e-encryption>

OpenPGP in Thunderbird - HOWTO and FAQ
<https://support.mozilla.org/en-US/kb/openpgp-thunderbird-howto-and-faq>

