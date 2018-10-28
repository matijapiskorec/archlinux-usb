# Simple terminal (ST)

Clone st and some patches:
```
git clone git://git.suckless.org/st
cd st
mkdir patches
cd patches
wget https://st.suckless.org/patches/alpha/st-alpha-20180616-0.8.1.diff
```

Apply patches:
```
patch < patches/[patch.diff]
```

Compile and install:
```
sudo make clean install
```

You can now run st with:
```
st
```
