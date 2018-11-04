# Install Jupyter notebook on Arch Linux

Jupyter notebook is available on official Arch repositories. You can install it with:
```
sudo pacman -S jupyter-notebook
```

Enable interactive Javascript widgets in notebooks:
```
sudo jupyter nbextension enable --py --sys-prefix widgetsnbextension
```

Install pip for Pyton packages:
```
sudo pacman -S python-pip
```

Python 2 used `virtualenv` module for creating virtual environments, but in Pyhton 3 it's recommened to use built in `venv` module:
```
mkdir python-virtual-environments
python3 -m venv science
```

Activate it:
```
source science/bin/activate
```

Deactivate it with:
```
deactivate
```

To use virtual environment with Jupyter notebook, you have to install custom kernel in virtual environment:
```
source projectname/bin/activate
pip install ipykernel
ipython kernel install --user --name=science
```

You can now install packages with `pip` or `pip3` and they will be visible in your Jupyter notebooks if you choose your custom `science` kernel:
```
pip install numpy
```
