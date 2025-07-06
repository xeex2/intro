For this demo session we shall use Docker, as it is nice and modular, and its installation process is simple. It is also possible not to use Hyper-V, crucial for users who do not use Windows Pro Editions. 

# Downloads and Installations
download and install [VcXsrv (~50MB)]( https://sourceforge.net/projects/vcxsrv/)

download and install [WSL (~300MB)](https://github.com/microsoft/WSL/releases/download/2.5.9/wsl.2.5.9.0.x64.msi)

Once installation is complete, open wsl settings app > networking tab: change networking mode to `nat` network 

<!-- reboot needed but will do in next step -->

download and install [docker desktop (~600MB)](https://docs.docker.com/desktop/)

Make sure you check `Use WSL 2 instead of Hyper-V` option in the installation dialog

On completion, click close and restart

# Docker Verification

On reboot run docker, skip account creation


To verify docker is working well open terminal and run 
```
docker run hello-world
```
It should pull an image then show a message confirming success. 

Still on terminal run 
```
docker pull codewithlennylen/rdj-2024
```
It will download a large image file (~2GB) that contains ROS2 humble and dependencies


Once finished, go to images tab. Press the play icon on the `codewithlennylen/rdj-2024` image. Click the optional settings and assign a convenient name. Then click run. A container should be created and running.

<!-- docker run -it --name rdj-2024 --privileged --network host --env DISPLAY=$DISPLAY codewithlennylen rdj-2024 -->

# Gui Setup
So far Docker will run, but graphical applications will crash on launch. These steps will fix that
## VcXsrv Setup


* launch Xlaunch.exe app
* choose multiple windows, click next
* choose no client, click next
* leave defaults (clipboard, Primary Selection, Native opengl), click next
* click save configuration, choose a convenient directory like Desktop
* Click finish

A server should be created using the config you've just created. To start the VcXsrv server with the same settings again, just run the config file you saved earlier. 
