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

## Installing Miniconda and Anaconda on a server without sudo privileges and without GUI

You can install Miniconda on a server without sudo privileges and without GUI by following this guides (do it in silent mode so you don't use gui!):
<https://docs.conda.io/projects/conda/en/latest/user-guide/install/linux.html>:
<https://docs.conda.io/projects/conda/en/latest/user-guide/install/macos.html#install-macos-silent>
```
wget https://repo.anaconda.com/miniconda/Miniconda3-latest-Linux-x86_64.sh
bash ~/Miniconda3-latest-Linux-x86_64.sh -b -p $HOME/miniconda
```

If installation didn't asked you about running conda init you have to do it yourself:
```
source ~/miniconda/bin/activate 
conda init
```

You will have to close and open your terminal window and then can enter conda environment.

Now you can install some package, for example powerlaw package for fitting powerlaws to data:
```
conda install -c conda-forge powerlaw
```

