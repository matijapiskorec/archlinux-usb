# Anaconda

Anaconda is a free distribution of Python and R programming languages and their llibraries. Anaconda is available in AUR:
```
git clone https://aur.archlinux.org/anaconda
cd anaconda
makepkg -si
```

Hmm, the full Anaconda ditribution is over 3 GB! So I will not install it for now, because I only need it for graph-tool for now (I already have Jupyter notebook and other Python packages through pip). 

## Installing graph-tool in Anaconda

graph-tool is a high-performance network analysis and visualization library written in C++ by Tiago Peixoto. Installation instructions for the Anaconda are here (from the SSDS 2020 summer school on data science):
<https://github.com/SSDS-Croatia/SSDS-2020/tree/master/Day-3>

The procedure is the following:
```
conda create --name gt -c conda-forge graph-tool
conda activate gt
conda install -n gt -c conda-forge ipython jupyter
```

