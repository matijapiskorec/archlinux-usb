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

To generate a new random password of length 8 for a particular service (argument `-n` or `--no-symbols` is to generate a password without symbols!) run:
```
pass generate -n service.com/user@service.com 8
```

You can edit a password in your default text editor:
```
pass edit service.com/user@service.com
```

You can additionally initialize a password store as a git repository, which will automatically make a commit each time you generate a new password:
```
pass git init
```

## Reneving an expired key

If your key associated with your password store expired you might have problems while inserting or retrieving you passwords.

Check your GPG keys: `gpg --list-keys`
Edit your GPG key: `gpg --edit-key <user-id>`

Once in the edit key sub menu you can run commands:

Change passphrase: `passwd`
Change the key expiration date: `expire`

## Reencrypting the password store

You can reencrypt your password store with a completelly new key.

First, generate a new key pair: `gpg --full-key-gen`
Check the newly generated key ID: `gpg --list-keys`
Optionally, you can edit the key and add additional users: `gpg --edit-key [KEY-ID]`
Now you can reencrypt the password store: `pass init [KEY-ID]`

## Backuping and generating Google Authentificator 2FA OTP ant TOTP codes

I created a backup of my Google Authentificator accounts using QR codes as screenshots. Here is the procedure how to backup them with pass and generate OTP codes from them.

You can extract text from QR codes using zbar, install it through Pacman:
```
sudo pacman -Sy zbar
```

You can now parse the QR code stored in image:
```
zbarimg -q --raw qr-code-image.png
```

However, Google Authentificator QR code does not have a standard URI:
```
otpauth-migration://offline?data=xxxxxxx
```

Unfortunatelly this cannot be used to generate OTP tokens directly. The URI format is described here:
<https://alexbakker.me/post/parsing-google-auth-export-qr-code.html>

Luckily, there is a parser in Javascript and shell script which also uses zbar:
<https://gist.github.com/mapster/4b8b9f8f6b92cc1ca58ae5506e0508f7>

Follow the instructions to install and run the parser:
1. Download the files package.json, index.js, migration-payload.proto and otp-codes.sh to an empty directory
2. Install dependencies through npm: `npm install`
3. Make otp-codes.sh executable: `chmod +x otp-codes.sh`
4. Extract codes: `./otp-codes.sh qr-code-image.png`

You will get following output:
```
> ./otp-codes.sh qr-code-image.png
Parsing: otpauth-migration://offline?data=XXXXXXXXXXXXXXXXXXXXXX
-----------------------
Issuer: Service-Provider
Name: name.surname@gmail.com
Secret: XXXXXXXXXXXXXXXXXX
-----------------------------------
```

You can use this Secret, Name and Issuer data to import into pass-otp - an extension for pass that generates OTP passwords:
<https://github.com/tadfisher/pass-otp>

Instructions for using pass-otp are in the next section. Here I will show how to use OATH Toolkit to produce OTP passwords manually, directly from secret:
<https://www.nongnu.org/oath-toolkit/>

Install it through Pacman:
```
sudo pacman -Sy oath-toolkit
```

This gives you oathtool which you can use to produce OTP passwords directly from secret:
```
oathtool --totp --base32 "XXXXXXXXXXXXXX"
```

More references of how to generate OTP keys in Arch Linux:

Initiative for Open Authentication
<https://wiki.archlinux.org/title/Initiative_for_Open_Authentication>

Google Authenticator
<https://wiki.archlinux.org/title/Google_Authenticator>

## Retrieving OTP passwords from pass

You can use pass-otp (an extension for pass) to store secrets and generate OTP passwords. You can install it through Pacman:
```
sudo pacman -Sy pass-otp
```

Lets create OTP password and store it under `Example/example-1` (this is `ISSUER/ACCOUNT` convention):
```
pass otp insert --secret --issuer "Example" --account "example-1"
```

This will prompt you for the secret for this token, which you have to type manually twice. If you have problems with copy/pasting into the interactive prompt, you can just type some random string and edit it later with:
```
pass edit Example/example-1
```

Find the corresponding place to enter your secret in the URI:
```
otpauth://totp/Example:example-1?secret=123&issuer=Example
```

Note that with this random secret string the generation of OTP password will not work! So you have to insert a secret in a correct format.

If you exclude the `--secret` option from the command above it would prompt you for the whole URI, but maybe it's better to insert only the secret.

Now if you want to generate an OTP password (add `-c` to do it in the clipboard and not in terminal):
```
pass otp code Example/example-1 -c
```

If you run it with the standard `pass` and not `pass otp` you will get just the URI string! However, you can use the standard pass to delete the entry:
```
pass rm Example/example-1
```

