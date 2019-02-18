# Encrypt and sign yout data with GnuPG

Install GnuPG:
```
sudo pacman -Syu gnupg
``` 

Generate a key pair:
```
gpg --full-gen-key
```

List keys with:
```
gpg --list-keys
```

Edit a key with:
```
gpg --edit-key <user-id>
```

For example, you can add an additional email address with `adduid` or change the passphrase with `passwd`.
