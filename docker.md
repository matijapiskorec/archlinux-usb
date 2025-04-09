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

For some common tasks you might need to install docker-compose as well:
```
sudo pacman -Syu docker-compose
```

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

## Managing Docker containers

List Docker containers:
```
docker container ls
```

Kill a container:
```
docker kill NAME
```

List all Docker images:
```
docker images --all
```

Remove a container:
```
docker rm NAME
```

## Installing pip packages with docker-compose

Docker compose installing requirements.txt
<https://stackoverflow.com/questions/41381350/docker-compose-installing-requirements-txt>

This is not working for me! :-(

```
version: "3"

services:

  stellar:
    image: python:3    
    container_name: stellar
    
    volumes:      
      - .:/project
    tty: true    
    working_dir: /project    
    command: /bin/bash 
    environment:                
        PYTHONPATH: "/project"
    depends_on:
      - requirements

  requirements:
    image: python:3
    volumes:
      - .:/project
    working_dir: /project
    command: pip install --no-cache-dir -r requirements.txt
```

## Build a simple Docker image which runs a Python scrip and saves the output to a file

Create a Dockerfile:
```
# Use the official Python image from Docker Hub
FROM python:3.8.18-slim-bullseye
ARG USER_ID
ARG GROUP_ID
# Set the working directory in the container
WORKDIR /workspace

# Linux dependencies
RUN apt-get update && \
  apt-get install -y build-essential sudo unzip bzip2 autoconf && \ 
  rm -rf /var/lib/apt/lists/*
  
# Copy the Python script into the container
COPY . /workspace

# update and install packages in python
RUN pip install --upgrade pip && \
  pip install -r requirements.txt
RUN echo $(ls -a)

# Add your user to the environment helps with mounts and creating and saving files
RUN groupadd -g $GROUP_ID user
RUN useradd user -u $USER_ID -g $GROUP_ID -m -s /bin/bash
USER user

# Run the Python script
CMD ["python", "helloworld.py"]
```

There are three files in the directory:

- Dockerfile - the file above
- requirements.txt - with pip requirements
- helloworld.py - a simple Python script that outputs results in a file

Build the Docker image while passing the user and group ID:
```
docker build -t matija:python38 --build-arg USER_ID=$(id -u) --build-arg GROUP_ID=$(id -g) .
```

Run the container while mounting the directory so that it creates the output file with the same permissions as your local user:
```
docker run -v /home/matija/tmp/download/test-vm/:/workspace/ matija:python38
```


