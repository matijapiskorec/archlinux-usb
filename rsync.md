# Synchronize directories with rsync

Copy (synchronize) remote folder to local over ssh:
```
rsync -avzhe ssh --progress user@server:~/folder .
```

Copy (synchronize) local folder to remote over ssh:
```
rsync -avzhe ssh --progress /folder user@server:~/folder
```

If your destination directory has some files which are not in source, by default they will remain. Use `--delete` option to delete them at the destination directory also. Following command will copy files from remote to local, making sure to delete local files which are not on remote:
```
rsync -avzhe ssh --progress --delete user@server:~/folder .
```

You can always add a dry run option `--dry-run` which will output results without actually copying anything.
