# Node.js Javascript on the server side

Node.js is a Javascript runtime environment. Install it from the official Arch repository, along with the Node package manager npm:
```
sudo pacman -Syu nodejs npm
```

To install npm package:
```
npm install [PACKAGE]
```

This installs the package in current directory under `node_modules`. For global installation use:
```
npm -g install [PACKAGE]
```

This installs package in `/usr/lib/node_modules/npm` and requires root privileges to do so.

To list all installed packages (the list is quite deep so `--depth=0` is used to show just the first level):
```
npm list --depth=0
```

## Browserify NPM modules

Browserify NPM modules (which are meant to be used with Node.js, not in browser). By following the guide here:
<https://stackoverflow.com/questions/49562978/how-to-use-npm-modules-in-browser-is-possible-to-use-them-even-in-local-pc>

Install everything required - browserify and the needed modules (in this case, NPM module for PCA analysis):
```
npm install -g browserify
npm install ml-pca
```

Write a simple main.js as a wrapper:
```
var PCA = require('ml-pca').PCA
global.window.PCA = PCA
```

Compile everything using browserify:
```
browserify main.js -o pca.js
```

Now, you could use pca.js inside the HTML file. You can do the same with the multiple NPM modules and bundle them all together in a single Javascript file.

## Programming tips

Reading and writing to a file: <https://nodejs.dev/learn/writing-files-with-nodejs>

The easiest way to read directly from a (JSON formated) file:
```
let file = require("./file.json");
```

Write to a file:
```
const fs = require('fs')
const content = 'Some content!'
fs.writeFile('test.txt', content, { flag: 'a+' }, err => {})
```

You can also write to a standard output which you can later redirect to a file (we are also writting a progress percentage to standard error):
```
process.stderr.write('\rProgress: '+(100*(1/(N.length**2))).toFixed(2)+'% ');
process.stdout.write(content);
```

Redirect output to a file:
```
node script.js >> file.txt
```

You can also compress the stream with gzip or bzip2 (about 25% smaller than gzip) in real time:
```
node script.js | gzip > file.txt.gz
node script.js | bzip2 > file.txt.bz2
```

This, however, will not write continuously to a compressed file with a constant memory footprint, but will store intermediarry result in memory!

