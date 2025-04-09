# nushell in Arch Linux

nushell is a new type of shell with structured output (not POSIX compliant!):
<https://wiki.archlinux.org/title/Nushell>
<https://www.nushell.sh/>

You can install it with:
```
sudo pacman -Syu nushell
```

And run it with `nu`.

List files larger than 10MB:
```
ls | where size > 10MB
```

It can read structured files like CSV without problem:
```
open file.csv | first 10
```

