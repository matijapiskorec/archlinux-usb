# Compression with zip

Install zip and unzip packages for compression:
```
sudo pacman -Syu zip unzip
```

Zip all files in a directory recursivelly:
```
zip -r archivename.zip directory/
```

Unzip files into a specified directory:
```
unzip archivename.zip -d directory/
```

Update or add a new file in zip archive:
```
zip -u archivename.zip newfile.txt
```

Remove a file from a zip archive:
```
zip -d archivename.zip file-for-removal.txt
```

Zip all jpeg files in directory:
```
zip archivenme.zip directory/*.jpeg
```

## Compression with gzip

Compress file and keep the original:
```
gzip -c file.txt > file.txt.gz
```

Uncompress in place:
```
gzip -d file.gz
```

Uncompress and pipe to stdout:
```
gzip -dc > file
```

## pigz

pigz offers parallel implementation of gzip. Install it with:
```
sudo pacman -Syu pigz
```

## Unzip multiple files with xargs

You can use find and xargs to unzip large number of zip archives:
```
find ~/path/ -type f -name "*.zip" -print0 | xargs -0 -n 1 unzip
```

Option `-n 1` is needed because otherwise xargs will try to feed one unzip command with multiple arguments, while we want at most one argument - one for each filename in the input. Additionally, you can unzip everything to standard output and search through all the lines with fzf (option `-e` is for exact matches):
```
find ~/path/ -type f -name "*.zip" -print0 | xargs -0 -n 1 unzip -p | fzf -e
```

## tar

To extract the `.tar.bz2` archive to a specific directory:
```
tar -xvf archive.tar.bz2 -C /directory
``` 

