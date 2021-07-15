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

You can check whether you are in virtual environment with:
```
pip -V
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

To upgrade a package which is already installed:
```
pip install --upgrade numpy
```

Some useful packages to install into science environment: 
```
pip install numpy matplotlib pandas cython sklearn xlrd 
```

For PyMC3 make sure you have hdf5 package installed, only then you can install pymc3 into your kernel:
```
sudo pacman -Syu hdf5
source ~/dev/env/science/bin/activate
pip install pymc3
```

To run jupyter notebook in a specific directory run:
```
jupyter notebook --notebook-dir=[NOTEBOOK DIRECTORY]
```

To list all running notebook servers:
```
jupyter notebook list
```

To stop a notebook server (if there is only one running you don't have to specify a name):
```
jupyter notebook stop
```

## Virtual environment in fish shell

Python virtual environments are configured to work in bash only, you cannot source environment to fish shell directly. However there are separate activate scripts for csh and fish shells which are created automatically upon environment creation! So you just have to:
```
source $HOME/[PATH TO ENV]/bin/activate.fish
```

This is from the official venv documentation:
<https://docs.python.org/3/tutorial/venv.html>

    (This script is written for the bash shell. If you use the csh or fish shells, there are alternate activate.csh and activate.fish scripts you should use instead.)

The remainder of this section are some old solutions which I leave here as a reference, but I now prefer the solution above. 

One way to activate virtual environment in fish shell is this (run in fish shell):
```
exec bash -c "source $HOME/[PATH TO ENV]/bin/activate; exec fish"
```

You can now check to which environment does your pip points to:
```
pip -V
```

There will be no usual environment name appended to the front of your prompt. This is because it is actually appended to the bash's PS1 variable which is not used by fish shell. To check this:
```
echo $PS1
```

Should print just `(env-name)`.

You can also try virtualfish for managing virtualenv environments in fish shell:
<https://riptutorial.com/python/example/9956/using-virtualenv-with-fish-shell>

## Managing your local Python pip installation

Instructions in this section follow official Python packaging documentation:
<https://packaging.python.org/guides/installing-using-pip-and-virtual-environments/>

A recommendation is to bootstrap a user installation of pip using the system pip:
```
python3 -m pip install --user --upgrade pip
```

Now you can check the version of pip and verify that it is installed in your home directory:
```
python3 -m pip --version
pip 9.0.1 from $HOME/.local/lib/python3.6/site-packages (python 3.6)
```

Installing directly from source (check that `setup.py` is present in the source folder!):
```
cd source-folder
pip install .
```

Install from a local archive:
```
pip install archive.tar.gz
```

Install packages from a different index than Python Package Index (PyPI):
```
pip install --index-url http://index.example.com/simple/ SomeProject
```

Upgrade a package in place:
```
pip install --upgrade package
```

Install packages from requirements file:
```
pip install -r requirements.txt
```

You can create requirements.txt file like this:
```
pip freeze > requirements.txt
```

You can use `pip freeze` as well as `pip list` to list all packages, but the freeze variant outputs in format which is suitable to be loaded back with pip for installation.

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

## Change default browser

In order to change the default web browser that is run at startup, first create Jupyter config:
```
jupyter notebook --generate-config
```

This will generate `.jupyter/jupyter_notebook_config.py`. There find the following line, uncomment it and add the path to your browser:
```
c.NotebookApp.browser = ''
```

Depending on the browser, you might add the `%s` argument, for example for surf browser:
```
c.NotebookApp.browser = '/usr/local/bin/surf %s'
```

## Exporting

To export to HTML without code blocks:
```
jupyter nbconvert path/to/your/ipynb --to=html --TemplateExporter.exclude_input=True --no-prompt
```

Regardless of you current directory, the output file will be in the directory of your notebook! You can change `--to=html` flag to `--to=pdf` to export to PDF, but for some reason the images are not displayed at all? Anyway, for now I just export to HTML and then print to PDF from browser.

## Installing tensorflow

Unfortunatelly, Tensorflow currently does not support Python 3.8 which is the default version in Arch Linux, only versions up to Python 3.7. Once you install appropriate version of Python you can install Tensorflow for a specific version using links provided on tensorflow website. I had problems installing Python 3.7 from AUR but Python 3.6 worked fine:
```
cd ~/src/
git clone https://aur.archlinux.org/python36.git
cd python36
makepkg -sri
```

If you are using fish as your shell make sure you switch it to bash, as there will otherwise e problems while entering the virtual environment:
```
bash
```

Now create Python3.6 virtual environment:
```
cd ~/dev/env/
python3.6 -m venv tensorflow
source tensorflow/bin/activate
pip install ipykernel
ipython kernel install --user --name=tensorflow
```

For example, for Python 3.6 CPU-only version:
```
pip install --upgrade https://storage.googleapis.com/tensorflow/linux/cpu/tensorflow_cpu-2.1.0-cp36-cp36m-manylinux2010_x86_64.whl
```

Or you can simply do:
```
pip install --upgrade tensorflow
```

Now you installed Tensorflow! Unfortunatelly, trying to import tensorflow module throws an error ("Illegal instruction (core dumped)"):
```
python -c "import tensorflow as tf;print(tf.reduce_sum(tf.random.normal([1000, 1000])))"
```

This is because my current processor does not support some advanced instructions which are used in newer version of Tensorflo (currently in version 1.15). In particular, AVX and AVX2 instruction sets are not supported on my processor. You can check which instruction sets are supported by your processor by running:

```
more /proc/cpuinfo | grep flags
```

Which outputs this on my laptop:
```
flags: fpu vme de pse tsc msr pae mce cx8 apic sep mtrr pge mca cmov pat pse36 clflush dts acpi mmx fxsr sse sse2 ht tm pbe syscall nx rdtscp lm constant_tsc arch_perfmon pebs bts rep_good nopl xtopology nonstop_tsc cpuid aperfmperf pni pclmulqdq dtes64 monitor ds_cpl vmx smx est tm2 ssse3 cx16 xtpr pdcm pcid sse4_1 sse4_2 popcnt aes lahf_lm pti tpr_shadow vnmi flexpriority ept vpid dtherm
ida arat
```

Notice there are no `avx` nor `avx2`. It seems that only Tensorflow 1.5 or earlier supports older processors. It is also possible to compile Tensorflow yourself while excluding the offending flags, which would have unkonwn consequences. There are some custom builds for Tensorflow 1.10 on the following Github repo:
<https://github.com/amikelive/tf-build>

Other than that, you can try to downgrade to 1.5:
```
pip uninstall tensorflow
pip install tensorflow==1.5
```

You can check that the new installation runs without errors:
```
python -c 'import tensorflow as tf; print(tf.__version__)'
```

## Installing pip modules from Github

You can install pip modules directly from Github if they are available there. This is useful to get the newest versions of modules:

```
git clone https://github.com/pathpy/pathpy pathpy3
cd pathpy3
pip install -e .
```

