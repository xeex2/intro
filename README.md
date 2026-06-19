# Introduction
You can use ROS2 Humble on [Ubuntu 22.04 or Windows ](https://docs.ros.org/en/humble/Installation.html) 

For this demo session we shall use an Ubuntu 22.04 container in Docker, as it is nice and modular, and its installation process is simple. It is also possible not to use Hyper-V, crucial for users who do not use Windows Pro Editions. 

You can use a terminal app of your choosing, Windows Powershell will suffice. Windows Terminal App by Microsoft (downloaded from Microsoft store) is recommended.

# Caveats

* This was tested on Docker engine installed in WSL, and Docker engine on Ubuntu 22.04. You may prefer to skip docker and run it directly on WSL, or native Ubuntu 22.04 in which case instructions are also provided for native Ubuntu 22.04, and Ubuntu 22.04 distro on WSL
* You may prefer the official ros2 docker images, see [docker docs](https://docs.docker.com/guides/ros2/), [ros docs](https://docs.ros.org/en/humble/How-To-Guides/Run-2-nodes-in-single-or-separate-docker-containers.html) and [other docker images](https://hub.docker.com/_/ros/)
* Gazebo Classic went EOL in January 2025, so ros-humble-gazebo-ros2-control and ros-humble-gazebo-ros2-pkgs cannot be installed using apt. Instead, they need to be manually cloned into the workspace (humble branch) alongside the other packages. During testing, only gazebo-ros2-control was problematic, so that has been added. 

# Environment setup
## Docker
### Downloads and Installations
download and install [WSL (~300MB)](https://github.com/microsoft/WSL/releases/download/2.5.9/wsl.2.5.9.0.x64.msi)

Once installation is complete, open wsl settings app > networking tab: change networking mode to `nat` network 

On completion, click close and restart your machine

On reboot run "Ubuntu" (i.e. the WSL distro)
Then follow the respective guide for your distro to [install docker engine](https://docs.docker.com/engine/install/)

### Verification

To verify docker is working well run this on the terminal
```bash
docker run hello-world
```
It should pull a small docker image then show a message confirming success. 

### Clone Intro and build the container
Still on terminal run 
```bash
git clone --depth 1 https://github.com/xeex2/intro.git
cd intro/src
```

Download the dependencies (~1GB) and build the docker image. Be please be patient until this command completes
```bash
docker build -t pancake_img .
```

once done
```bash
cd ..
```


### Create the docker container
create container with this (WSL)
```bash
docker run -it -w /home/pancake --name=pancake_cont --user=pancake --net=host --ipc=host --env DISPLAY=$DISPLAY -v /tmp/.X11-unix/:/tmp/.X11-unix/ pancake_img
```

create container with this (Ubuntu)
```bash
docker run -it -w /home/pancake --name=pancake_cont --user=pancake --net=host --ipc=host --device /dev/dri --env DISPLAY=$DISPLAY -v /tmp/.X11-unix/:/tmp/.X11-unix/ --device=/dev/ttyACM0:/dev/ttyACM0 pancake_img
```
The `--env ...`, `-v /tmp/ ...` and `--device ...` arguments should pass gui from the docker container to the host. 
The `--device` arg passes the USB microcontroller. Make sure you edit that field to the correct path

to start an existing container
```bash
docker start -ai pancake_cont
```

to attach your terminal onto a running container
```bash
docker attach pancake_cont
```

to create a new terminal on a running container
```bash
docker exec -it pancake_cont bash
```

## Native Ubuntu 22.04 or Ubuntu 22.04 distro on WSL
In case docker is not your thing, you can use the ROS environment installed on your platform. The official guide for installing ROS2 humble is [here](https://docs.ros.org/en/humble/Installation/Ubuntu-Install-Debs.html). Then run this bash snippet to install the dependencies 
```bash
sudo apt-get update && \
sudo apt-get install -y --no-install-recommends \
    nano sudo \
    x11-apps python3-pip \
    ros-humble-demo-nodes-cpp \
    ros-humble-teleop-twist-keyboard \
    ros-humble-xacro \
    ros-humble-twist-mux \
    ros-humble-robot-localization \
    ros-humble-ros2-control \
    ros-humble-ros2-controllers \
    ros-humble-rplidar-ros \
    ros-humble-slam-toolbox \
    ros-humble-navigation2 \
    ros-humble-nav2-bringup \
    ros-humble-rviz2 \
    gazebo libgazebo-dev ros-humble-gazebo-ros-pkgs
```

then set up the workspace
```bash
git clone --depth 1 https://github.com/xeex2/intro.git
cd intro
```

# Building the Intro Repo

Once that is complete
```bash
colcon build --symlink-install
echo "source ${PWD}/install/setup.bash" >> ~/.bashrc
source ~/.bashrc
```
This should build the new workspace

whenever you add a new file or package you need to run
```bash
colcon build --symlink-install
source install/setup.bash
```

# Talker-Listener Demo

run 
```bash
ros2 run demo_nodes_cpp talker
```
and in another terminal run 
```bash
ros2 run demo_nodes_cpp listener
```
and in another run 
```bash
rqt_graph
```
Once done close with Ctrl+C

# Turtlesim Demo
run 
```bash
ros2 run turtlesim turtlesim_node
```
and in another terminal run 

```bash
ros2 run turtlesim turtle_teleop_key
``` 
and in another run 
```bash
rqt_graph
```
Click to focus the terminal window where `turtle_teleop_key` was launched and press the arrow keys. The robot should move. 

Once done close using Ctrl+C

# Gazebo Demo
in one terminal cd into intro then launch rviz
```bash
rviz2 -d ./src/comp.rviz
```
in another launch the simulation, make sure you are at the into directory
```bash
ros2 launch jkl launch_sim.launch.py use_sim_time:=true world:=./src/jkl/worlds/dojo2024
```
then in another terminal
```bash
ros2 run teleop_twist_keyboard teleop_twist_keyboard
```
Click to focus the terminal window where teleop_twist_keyboard was launched, and press any of these keys `u i o j k l m , .` to drive the robot. 

## For mapping phase
run this, make sure you are in the intro directory
```bash
ros2 launch jkl online_async_launch.py slam_params_file:=./src/jkl/config/mapper_params_online_async.yaml use_sim_time:=true
```
With the teleop_twist_keyboard terminal in focus use `u i o j k l m , .` to drive the bot around until a satisfactory map is shown in rviz

Open slam toolbox panel in rviz and fill the input boxes with a desired name. Click save map and serialize map. Four map files will be saved in current directory

## For navigation phase
Kill online_async then run  
```bash
ros2 launch jkl localization_launch.py map:=<path_to_your_map>.yaml use_sim_time:=true
```
To set/change pose estimate, you can use rviz
in another terminal run this, make sure you are in the intro directory
```bash
ros2 launch jkl navigation_launch.py map_subscribe_transient_local:=true params_file:=./src/jkl/config/nav2_params.yaml use_sim_time:=true
```
Use rviz to set waypoints either one by one or all points at once. Navigate through poses creates one path across all waypoints while navigate to waypoints moves the robot to each point one-by-one

When you're done, kill every terminal process using Ctrl+C

# Other Resources
* ROS introduction course [here](https://www.youtube.com/watch?v=0aPbWsyENA8&list=PLLSegLrePWgJudpPUof4-nVFHGkB62Izy)
* A great channel for [ROS2 Jazzy](https://www.youtube.com/@automaticaddison)
* Full robot building guide including simulation [here](https://www.youtube.com/watch?v=OWeLUSzxMsw&list=PLunhqkrRNRhYAffV8JDiFOatQXuU-NnxT)
* ROS2 development [in Docker](https://docs.docker.com/guides/ros2/)
* ROS introduction book provided [in repo](ROS_2_from_Scratch_-_Edouard_Renard.pdf)

