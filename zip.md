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

Unzip files to standard output, works even on password protected files:
```
unzip -p archivename.zip
```

Uncompress archive (or a list of archives, can be provided from standard input) and pipe it to standard output. Identical to `gunzip -c`:
```
zcat archivename.zip
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
zip archivename.zip directory/*.jpeg
```

Zip can also be used as a simple way to encrypt a file with a password, just pass the `-e` flag (`--encrypt`):
```
zip -e archivename.zip file.jpeg
``` 

## Compression with gzip

Compress file and keep the original. This is done by writting output to standard output with option `-c` which preserves the input file and is also very memory efficient (memory footprint is almost nill!):
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

## rar and 7z

This is a copy of instructions from lakka.md. Install required decompressers:
```
sudo pacman -Syu unrar
sudo pacman -Syu p7zip 
```

Now you can decompress rar and 7z archives:
```
unrar x [RAR ARCHIVE] destination-directory/
7z e [7Z ARCHIVE]
```

