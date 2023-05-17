# tar - an archiving utility

`tar` should be available on almost all Linux systems.

Create a `tar.gz` archive:
```
tar cvfz archive.tar.gz *.txt
```

Extract a `tar.gz` archive:
```
tar xvzf archive.tar.gz
```

Basic options:
`c` compress/create
`x` extract
`f` archive with a given filename
`v` verbose
`z` use gzip (both for compressing and decompressing)

Extract it into a specific directory (has to exist previously!):
```
tar xvzf archive.tar.gz -C directory/
```

If you want to extract a specific file you have to provide a full path in the archive, however, it will be extracted with that path. You can strip the path and extract the file directly into the current directory with `--strip-components`:
```
tar xvzf archive.tar.gz subdirectory-within-archive/file.txt --strip-components 1
```

