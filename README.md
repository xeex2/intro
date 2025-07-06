# Introduction
For this demo session we shall use Docker, as it is nice and modular, and its installation process is simple. It is also possible not to use Hyper-V, crucial for users who do not use Windows Pro Editions. 

You can use a terminal app of your choosing, Windows Powershell will suffice. Windows Terminal App by Microsoft is recommended.

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
then paste the following line at the **end** of the file, use Ctrl+End to skip to end, then move the cursor using the arrow keys
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
cd /home/rdj-2024
git clone https://github.com/xeex2/intro.git
```

Once finished:

```
cd intro/src 
chmod +x init.bash
./init.bash
```

Once that is complete
```
source ~/.bashrc
cd ..
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

# Turtlesim Demo
run 
```
ros2 run turtlesim turtlesim_node
```
and in another terminal run 

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
in one terminal cd into intro then launch rviz
```
rviz2 -d ./src/comp.rviz
```
in another launch the simulation, make sure you are at the into directory
```
ros2 launch jkl launch_sim.launch.py use_sim_time:=true world:=./src/jkl/worlds/dojo2024
```
then in another terminal
```
ros2 run teleop_twist_keyboard teleop_twist_keyboard
```
Click to focus the terminal window where teleop_twist_keyboard was launched, and press any of these keys `u i o j k l m , .` to drive the robot. 

## For mapping phase
run this, make sure you are in the intro directory
```
ros2 launch jkl online_async_launch.py slam_params_file:=./src/jkl/config/mapper_params_online_async.yaml use_sim_time:=true
```
With the teleop_twist_keyboard terminal in focus use `u i o j k l m , .` to drive the bot around until a satisfactory map is shown in rviz

Open slam toolbox panel in rviz and fill the input boxes with a desired name. Click save map and serialize map. Four map files will be saved in current directory

## For navigation phase
Kill online_async then run  
```
ros2 launch jkl localization_launch.py map:=<path_to_your_map>.yaml use_sim_time:=true
```
To set/change pose estimate, you can use rviz
in another terminal run this, make sure you are in the intro directory
```
ros2 launch jkl navigation_launch.py map_subscribe_transient_local:=true params_file:=./src/jkl/config/nav2_params.yaml use_sim_time:=true
```
Use rviz to set waypoints either one by one or all points at once. Navigate through poses creates one path across all waypoints while navigate to waypoints moves the robot to each point one-by-one

When you're done, kill every terminal process using Ctrl+C

# Other Resources
* ROS introduction course [here](https://www.youtube.com/watch?v=0aPbWsyENA8&list=PLLSegLrePWgJudpPUof4-nVFHGkB62Izy)
* Full robot building guide including simulation [here](https://www.youtube.com/watch?v=OWeLUSzxMsw&list=PLunhqkrRNRhYAffV8JDiFOatQXuU-NnxT)
* ROS introduction book provided [in repo](ROS_2_from_Scratch_-_Edouard_Renard.pdf)

