# Anaconda

Anaconda is a free distribution of Python and R programming languages and their llibraries. Anaconda is available in AUR:
```
git clone https://aur.archlinux.org/anaconda
cd anaconda
makepkg -si
```

Hmm, the full Anaconda ditribution is over 3 GB! So I will not install it for now, because I only need it for graph-tool for now (I already have Jupyter notebook and other Python packages through pip). 

## Installing graph-tool in Anaconda

graph-tool is a high-performance network analysis and visualization library written in C++ by Tiago Peixoto. 

First, to install Miniconda on a remote server follow the instructions in section `Installing Miniconda on a remote server without sudo privileges (version 2)`.

Then follow the instructions for installing the graph-tool with Anaconda
<https://git.skewed.de/count0/graph-tool/-/wikis/installation-instructions>

The procedure is the following:
```
conda create --name gt -c conda-forge graph-tool
conda activate gt
```

Install any additional packages with
```
conda install -n gt -c conda-forge ipython jupyter numpy scipy pandas matplotlib
```

Quickstart using graph-tool
<https://graph-tool.skewed.de/static/doc/quickstart.html>

```
python3
from graph_tool.all import *
g = Graph()
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

## Installing Miniconda on a remote server without sudo privileges (version 2)

These are instructions for installing Miniconda on a remote Linux machine without sudo privileges, completelly through command line. First, connect to the machine:
```
ssh <USER>@<SERVER>
```

Check your Python 3 version:
```
python3 --version
```

In my case it is 3.8.10 so I download the Miniconda install script for Python 3.8 from official repository and ran it:
```
wget https://repo.anaconda.com/miniconda/Miniconda3-py38_4.11.0-Linux-x86_64.sh
chmod +x Miniconda3-py38_4.11.0-Linux-x86_64.sh
./Miniconda3-py38_4.11.0-Linux-x86_64.sh
```

If it prompts you to initialize the base environment with `conda init` you can say yes. After it finishes you will be automatically placed in base environment, also each time when you login to your shell. If you want to deactivate it you can run this command (restart your shell to take effect):
```
conda config --set auto_activate_base false
```

You can always activate and deactivate environments with these commands:
```
conda activate base
conda deactivate
```

Now create an environment for Jupyter notebook:
```
conda create -n <ENV-NAME> python=3.8
```

Activate it and install some basic modules, the most important one being Jupyter, but you can install others as well just to get you started:
```
conda activate <ENV-NAME>
conda install jupyter numpy scipy matplotlib
```

Run a tmux multiplexer session under which we will run our Jupyter server:
```
tmux new -s <SESSION-NAME>
```

Remember you can always detach from the tmux session with `Ctrl-b d` and reattach with:
```
tmux attach -t <SESSION-NAME>
```

Now you can activate the blocksci environment and run the Jupyter notebook server:
```
conda activate <ENV-NAME>
jupyter notebook --no-browser --port=1238
```

You can choose any port you want! Just make sure that Jupyter notebook is really running under the selected port - if the port is already taken it will automatically switch to another one, you will see this in output.

Also, before you detach from the tmux terminal make sure you copy the token which you will need to login in your local browser. You can also retrieve that token later by running (under the blocksci environment):
```
jupyter notebook list
```

Tokens looks like this:
```
token=9c3eb04d00...811b315970
```

Now go to your local machine and start an SSH tunnel to the Jupyter notebook on the remote machine:
```
ssh -N -f -L localhost:8321:localhost:1238 <USER>@<SERVER>
```

Now the first port is any one which you choose on your local machine (you can choose whatever, as long as it is free on your local machine), the second one is the port from the remote machine running Jupyter notebook. You can now go to your local browser in order to access Jupyter notebook, go to this URL address:
```
localhost:8321
```

First time when you connect you will probably have to input the token that you retriever earlier!

If after another login the `conda` command is not found, make sure to include this line in your `.zshrc` (or `.bashrc` if your are using Bash shell):
```
export PATH="$HOME/miniconda/bin:$PATH"
```

You can restart your terminal or just run:
```
source ~/.zshrc
```

## Installing Miniconda on my Arch Linux machine

Install Miniconda3 from AUR:
```
git clone https://aur.archlinux.org/miniconda3.git
cd miniconda3
makepkg -sri
```

Initialize conda for fish shell:
```
/opt/miniconda3/bin/conda init fish
```

This will add conda to your path so that you can use it from the fish shell, it adds this to your `~/.config/fish/config.fish`:
```
# >>> conda initialize >>>
# !! Contents within this block are managed by 'conda init' !!
eval /opt/miniconda3/bin/conda "shell.fish" "hook" $argv | source
# <<< conda initialize <<<
```

However, this makes openning each fish shell extremely slow! So I just commented this eval statement, but now the conda is not available in the fish shell anymore! If you want to enable it you have to run it manually and then you can use conda command:
```
eval /opt/miniconda3/bin/conda "shell.fish" "hook" $argv | source
```

Conda will activate base environment whenever you open a fish shell, to disable this behavior run the following command:
```
conda config --set auto_activate_base false
```

The benefit of Miniconda is that you can easily create Python environments with different versions, for example Python 2.7 for compatibility with older projects:
```
conda create --prefix ./env/python27 python=2.7
```

In the example above we created an environment with a prefix (rather than a name), meaning that the environemnt will reside in local directory. To activate it you have to use the prefix:
```
conda activate ./env/python27
```

You can now install packages inside with pip:
```
pip install numpy
```

