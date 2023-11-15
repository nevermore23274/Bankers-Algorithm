# Bankers-Algorithm


### Run Commands:
NOTE: If any folder in your pathing has spaces, ensure you place quotes around the -v command. This goes for all OS's. For example:
```
docker run --name assignment4 -v "C:\My Drive\<rest>:/assignment4" -it assignment4
```
## --- Docker ---
--- Linux ---
```
docker build -t assignment4:latest -f docker/Dockerfile .
```
```
docker run --name assignment4 -v <location>:/assignment4 -it assignment4
```
When coming back (the --name assigns a name to a container, so no need to do it again since you've already made the container)
```
docker run -v <location>:assignment4 -it assignment4
```
To clean up your system after you're done:
```
docker system prune --all
```
--- Windows ---
```
docker build -t assignment4:latest -f Docker/Dockerfile .
```
```
docker run --name assignment4 -v <drive>:<location>:/assignment4 -it assignment4
```
When coming back (the --name assigns a name to a container, so no need to do it again since you've already made the container)
```
docker run -v <drive>:<location>:/assignment4 -it assignment4
```
To clean up your system after you're done:
```
docker system prune --all
```
## --- Podman ---
--- Linux ---
```
podman build -t assignment4:latest -f docker/Dockerfile .
```
```
podman run --name assignment4 -v <location>:/assignment4:z -it assignment4
```
When coming back (the --name assigns a name to a container, so no need to do it again since you've already made the container)
```
podman run -v <location>:/assignment4:z -it assignment4
```
To clean up your system after you're done:
```
podman system prune --all
```
--- Windows ---
```
podman build -t assignment4:latest -f Docker/Dockerfile .
```
```
podman run --name assignment4 -v <drive>:<location>:/assignment4 -it assignment4
```
When coming back (the --name assigns a name to a container, so no need to do it again since you've already made the container)
```
podman run -v <drive>:<location>:/assignment4 -it assignment4
```
To clean up your system after you're done:
```
podman system prune --all
```
