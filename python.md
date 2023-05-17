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
