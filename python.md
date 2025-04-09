# Python

## Python debugger

To add a breakpoint in your Python code just add this line:
```
import pdb; pdb.set_trace()
```

In Python 3.7 you can add this instead:
```
breakpoint()
```

Debugger commands:
Print the list of all available commands: `h(elp)`
Print the stack trace: `w(here)`
Move up or down in the current frame (function): `u(p)`, `d(own)`
Execute the current line: `s(tep)`
Continue execution until next line is reached: `n(ext)`
Continue execution until current function returns: `r(eturn)`
Continue execution, only stop on next breakpoint: `c(ont(inue))`
List source code (also list longer source code): `l(ist)`, `ll`
Print the arguments of the current function: `a(rgs)`
Evaluate the expression and print its value (also, pretty print it): `p`, `pp`
Print the type of expression: `whatis`
Display value of expression if it change every time debugger stops: `display`
Enter a recursive debugger that steps through the code argument: `debug`
Quit debugging: `q(uit)`

For all debugger commands see official pdb documentation:
<https://docs.python.org/3/library/pdb.html>

Python debugger sometimes reports `NameError: name ... not defined` when trying to run list comprehension within pdb. This is because list comprehension in debugging only works in global scope, not while debugging a function. List comprehension scoping rules interact badly with cases where the variables present in enclosing scopes can't be determined statically, such as in debuggers or class bodies. Just run this command in debugger and then it should work:
```
globals().update(locals())
```

## Compilation of Python code

Numba is an open source JIT compiler that translates a subset of Python and NumPy code into fast machine code
<https://numba.pydata.org/>
<https://numba.readthedocs.io/en/stable/user/5minguide.html>

We can also use Nuitka for source-to-source compilation to C++:
<https://github.com/Nuitka/Nuitka>
<https://nuitka.net/doc/user-manual.html>

You can compile it in one of the following ways (the last one should be the most compact, creating a single binary):
```
python -m nuitka --follow-imports program.py
python -m nuitka --follow-imports --include-plugin-directory=plugin_dir program.py
python -m nuitka --standalone program.py
python -m nuitka --onefile program.py
```

This is the command that I use in one of my projects (note the use of plugin for multiprocessing if you are using this library!):
```
python3 -m nuitka --onefile --show-progress --show-modules --plugin-enable=multiprocessing program.py
```

I don't know whether `freeze_support()` is needed on Linux system or only on Windows:
<https://github.com/Nuitka/Nuitka/blob/develop/tests/programs/multiprocessing_using/MultiprocessingUsingMain.py>

```
from multiprocessing import freeze_support

if __name__ == "__main__":
    freeze_support()
```

Install Nuitka and patchelf (needed for standalone and onefile options on Linux):
```
pip install nuitka patchelf
```

I installed ccache from Pacman repositories so that parts of compilation can be cached in order to speed it up:
```
sudo pacman -Sy ccache
```

## pipx

pipx is allows you to install a pip package in an isolated environment which will not conflict with your global pip configuration. Use it for standalone Python packages which you want to use externally (for example, in a terminal as a standalone program rather than in Python interpreter) but you don't want an overhead of managing your own virtual environment. 

You can install pipx with Pacman:
```
sudo pacman -Sy python-pipx
```

Now you can check installed pipx packages with:
```
pipx list
```

And install any package you would otherwise install with pip, for example termgraph
```
pip install termgraph
```

Packages are installed in `~/.local/bin`, so they will not be accessible globally unless this path is in your PATH variable. To include it in your path variable you can do:
```
pipx ensurepath
```

Check how to enable completions for pipx for various shells:
```
pipx completions
```

For example, for my fish shell I just have to run this command once:
```
register-python-argcomplete --shell fish pipx >~/.config/fish/completions/pipx.fish
```

You can also install Python module from a git repository:
```
pipx install git+https://github.com/psf/black.git
```

pipx doesn't need sudo privileges as all packages are installed locally!

There is a `run` option which allows you to temporarily install a package and use it without actually installing it. For example you can install and run cowsay program with arguments:
```
pipx run cowsay Hello world!
```

## termgraph

A command-line tool that draws basic graphs in the terminal, written in Python.
<https://github.com/mkaz/termgraph>

Install it with pipx:
```
pipx install termgraph
```

Try it with:
```
printf 'label1 1\nlabel2 2' | termgraph
```

## Installing a specific Python version in a virtual environment

Python virtual environments don't have their own version of Python. Rather, they use Python which is available on the system. Because in Arch you always have the newest version of Python 3, as well as Python 2 as a separate package if you need it:
```
> python --version
Python 3.11.5
> python2 --version
Python 2.7.18
> python3 --version
Python 3.11.5
```

However, if you need an older version of Python 3, you have to install it separatelly through AUR:
```
git clone https://aur.archlinux.org/python39.git
cd python39/
makepkg -sri
```

You now have Python 3.9 version:
```
> python3.9 --version
Python 3.9.18
```

I wanted to install a project with its own requirement file where Python 3.9 was recommended. I created virtual environment using Python 3.9 (rather that Python 3.11. which was available on the system):
```
python3.9 -m venv /home/matija/dev/env/picoGPT
source ~/dev/env/picoGPT/bin/activate.fish
cd dev/repo/picoGPT/
pip install -r requirements.txt
```

To see all older Python versions in AUR:
<https://wiki.archlinux.org/title/Python>

