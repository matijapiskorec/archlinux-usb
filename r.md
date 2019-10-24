# R statistical programming

Install r package for statistical programming:
```
sudo pacman -Syu r
```

Install optional dependencies (also openblas, but it is in conflict with blas):
```
sudo pacman -Syu --asdeps tk gcc-fortran
```

To install packages from the closest CDN, run R console with `R` and then:
```
install.packages('ggplot2', repos='http://cran.us.r-project.org')
```

More information on R in Arch Linux:
<https://wiki.archlinux.org/index.php/R>

## Runing R with Jupyter notebook

In order to use R with Jupyter notebook you have to install IRkernel:
```
install.packages('IRkernel')
IRkernel::installspec()  # to register the kernel in the current R installation
```

You can now select IRkernel from the Jupyter notebook dropdown menu. If you want to start it with the IRkernel by default run:
```
jupyter notebook --kernel=ir
```

More information on:
<https://github.com/IRkernel/IRkernel>

## Rstudio

Rstudio environment is available in AUR repository:
```
git clone https://aur.archlinux.org/rstudio-desktop-bin.git
```

Then simply run `makepgk -sri` inside the directory to install it.

