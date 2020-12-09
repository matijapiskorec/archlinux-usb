# Tools for HTTP archives (HAR)

Contents of the browser can be exported as har files. Usefull tool for this is har-tools. Install it from Github like this:
```
cd ~/src
git clone https://github.com/outersky/har-tools.git
cd hart-tools
go build harx.go
mv harx ~/bin/.
```

List contents of har archive: `harx -l archive.har`
Extract content of har archive into current directory: `harx -x . archive.har`
