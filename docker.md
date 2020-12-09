# Docker - run any application in aa lightweight container

Install docker from official Pacman repository:
```
sudo pacman -Syu docker
```

Start the docker service:
```
systemctl enable docker.service
systemctl start docker.service
```

You can verify whether it's running with:
```
docker info
```

You might need to create a docker group and add your user to it:
```
sudo groupadd docker
sudo usermod -aG docker ${USER}
```

Check whether your user is added to the docker group:
```
cat /etc/group
```

There might be some problems while connected to the network, you might want to temporarily disconnect from your network while starting the docker service.

For more information check official Arch documentation:
<https://wiki.archlinux.org/index.php/Docker>

## Runing graph-tool in docker

How to run graph-tool in in docker instructions:
<https://git.skewed.de/count0/graph-tool/-/wikis/installation-instructions>

Pull the Docker image:
```
docker pull tiagopeixoto/graph-tool
```

Interactive session (command line):
```
docker run -it -u user -w /home/user tiagopeixoto/graph-tool ipython
```

For interactive visualizations enabled:
```
xhost +local:
docker run -ti -u user -w /home/user --rm -e DISPLAY=$DISPLAY -v /tmp/.X11-unix:/tmp/.X11-unix tiagopeixoto/graph-tool ipython
```

Jupyter notebook session:
```
docker run -p 8888:8888 -p 6006:6006 -it -u user -w /home/user tiagopeixoto/graph-tool bash
```

And then start the notebook within the session:
```
[user@c20b92b8c4bf ~]$ jupyter notebook --ip 0.0.0.0
```

You should now visit the notebook in your browser:
<http://localhost:8888/>

More information available on the SSDS 2020 school website:
<https://colab.research.google.com/github/count0/colab-gt/blob/master/colab-gt.ipynb>
<https://github.com/SSDS-Croatia/SSDS-2020/tree/master/Day-3>

Check all Docker images:
```
docker images
```

Remove a Docker image:
```
docker image rm image_name_or_id
```

