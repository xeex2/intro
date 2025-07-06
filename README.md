# Introduction
For this demo session we shall use Docker, as it is nice and modular, and its installation process is simple. It is also possible not to use Hyper-V, crucial for users who do not use Windows Pro Editions. 

You can use a terminal app of your choosing. Windows Terminal App by Microsoft is recommended.

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


Once finished, go to images tab. Press the play icon on the `codewithlennylen/rdj-2024` image. Click the optional settings and assign a convenient name. Then click run. A container should be created and run.

<!-- docker run -it --name rdj-2024 --privileged --network host --env DISPLAY=$DISPLAY codewithlennylen rdj-2024 -->

# Gui Setup
So far Docker containers will run, but graphical applications will crash at launch. These steps will fix that
## VcXsrv Setup


* launch Xlaunch.exe app
* choose multiple windows, click next
* choose no client, click next
* leave defaults (clipboard, Primary Selection, Native opengl), click next
* click save configuration, choose a convenient directory like Desktop
* Click finish

A server should be created using the config you've just created. To start the VcXsrv server with the same settings again, just run the config file you saved earlier. 


## Container Setup

open terminal and run 
```
ipconfig
``` 
and look for the `Ethernet adapter vEthernet (WSL)`
copy the ipv4 address e.g. `172.30.176.1`
start the container and run 
```
sudo su
```

then run 
```
nano ~/.bashrc
```
then paste the following line at the **end** of the file 
```
export DISPLAY=<your ip>:0.0
``` 
an example is 
```
export DISPLAY=172.30.176.1:0.0
```
Press Ctrl+S then Ctrl+X

# Cloning the Intro Repo

Next run 
```
git clone https://github.com/xeex2/intro.git
```

Once finished:

cd into src then
```
cd intro/src 
./init.bash
```

Then 
```
colcon build --symlink-install
```
This should build the new workspace. Build it once using the same command. 

then 
```
source install/setup.bash
```

# Talker-Listener Demo

run 
```
ros2 run demo_nodes_cpp talker
```
and in another terminal run 
```
ros2 run demo_nodes_cpp listener
```
and in another run 
```
rqt_graph
```
Once done close with Ctrl+C

# Turtelsim Demo
run 
```
ros2 run turtlesim turtlesim_node
```
and in another terminal run 
```
ros2 run turtlesim turtlesim_node
```
and in another
```
ros2 run turtlesim turtle_teleop_key
``` 
and in another run 
```
rqt_graph
```
Click to focus the terminal window where `turtle_teleop_key` was launched and press the arrow keys. The robot should move. 

Once done close using Ctrl+C

# Gazebo Demo

launch the simulation 
```
ros2 launch jkl launch_sim.launch.py use_sim_time:=true world:=./src/jkl/worlds/dojo2024
```

# Other Resources
* ROS introduction book provided in repo
* ROS introduction course [here](https://www.youtube.com/watch?v=0aPbWsyENA8&list=PLLSegLrePWgJudpPUof4-nVFHGkB62Izy)
* Full robot building guide including simulation [here](https://www.youtube.com/watch?v=OWeLUSzxMsw&list=PLunhqkrRNRhYAffV8JDiFOatQXuU-NnxT)

