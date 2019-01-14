# Jupyter notebook on Arch Linux

## Install Jupyter notebook through pacman

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

## Setting up Jupyter notebook on a remote machine

SSH to remote machine (probably after running separate screen session with `screen`):
```
jupyter notebook --no-browser --port=8889
```

Start an SSH tunnel on your local machine:
```
ssh -N -f -L localhost:8888:localhost:8889 remote_user@remote_host
```

You can now access the notebook from your local machine by visiting `localhost:8888` in your browser. Option `-f` will force SSH tunnel to go to the background. For security considerations see bellow.

Because SSH tunnel runs in the background you have to search for its process ID and kill it manually:
```
ps aux | grep localhost:8889
kill -15 12418
```


## Security on remote Jupyter notebooks

Starting from notebook version 4.3, every time a notebook launches it generates random token which the browser needs to authenticate, for example:
```
http://localhost:8889/?token=91d***e89
```

It is also possible to directly secure Jupyter notebook with a password. On a remote machine run:
```
jupyter notebook --generate-config
jupyter notebook password
```

Add the hashed password to your `jupyter_notebook_config.py` file, usually located in your home directory in `~\.juptyer`:
```
c.NotebookApp.password = u'sha1:67c***aed'
```

