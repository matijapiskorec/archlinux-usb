# Network traffic analysis and management with mitmproxy

Install mitmproxy using Pacman:
```
sudo pacman -Syu mitmproxy
```

## Setting up a reverse proxy

Start a simple Python HTTP server:
```
python3 -m http.server 8000
```

Then run a reverse proxy on port 8001 to port 8000:
```
mitmproxy -p 8001 -m reverse:http://127.0.0.1:8000 	
```

You can now connect to <https://localhost:8001/> although it will ask you for a security certificate exception because the certificate is self-signed. However, this is a simple way to provide SSL security and HTTPS connection for your local web project.

## Cheatsheet

Start proxy on port 8001
```
mitmproxy -p 8001 	
```

Reverse proxy on port 8001 to port 4000
```
mitmproxy -p 8001 -m reverse:http://127.0.0.1:4000 	
```

Stream flows to file as they arrive
```
mitmproxy -p 8001 -w traffic.mitm 	
```

Read flows from file
```
mitmproxy -r traffic.mitm 	
```

Replay client requests from a saved file
```
mitmproxy -C traffic.mitm 	
```

Replay server responses from a saved file
```
mitmproxy -S traffic.mitm 	
```

mitmproxy quick help
```
mitmproxy -h 	
```

To check the event log type `Ctrl-e` when inside mitmproxy (you can exit with `q`).

