# Get answers in your terminal using tuxi

Tuxi is a simple bash script which gives you answers in terminal:
<https://github.com/Bugswriter/tuxi>

Prerequisites:

pup - parsing HTML at the command line:
```
cd ~/src
git clone https://aur.archlinux.org/pup-git.git  
cd pup-git
makepgk -sri
```

recode - convert files between various characters and usages
```
sudo pacman -Syu recode
```

Now you can install tuxi:
```
cd ~/src
git clone https://github.com/Bugswriter/tuxi.git
cd tuxi
chmod +x tuxi
cp tuxi ../bin/
```

Example queries:
```
tuxi linus torvalds birthday
tuxi price of bitcoin in usd
tuxi daylight saving time
tuxi next solar eclipse
tuxi best games of 2019
tuxi does fructose make me fat
tuxi capital of senegal
tuxi age of joe biden
```


