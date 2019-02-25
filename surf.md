# Surf suckless web browser

Install surf suckless web browser with pacman:
```
sudo -Syu surf
```

You can also build it from source. First git clone the repository:
```
git clone https://git.suckless.org/surf
``` 

Now you can build it:
```
cd surf
sudo make clean install
```

If the build process fails because gcr package is missing you can install it through pacman:
```
sudo pacman -Syu gcr
``` 
