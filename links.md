download and install VcXsrv (~50MB) https://sourceforge.net/projects/vcxsrv/
download and install WSL (~300MB) https://github.com/microsoft/WSL/releases/download/2.5.9/wsl.2.5.9.0.x64.msi

Open wsl settings app > networking tab: change networking mode to `nat` network 
<!-- reboot needed but will do in next step -->

download and install docker desktop (~600MB) https://docs.docker.com/desktop/
make sure you check `Use WSL 2 instead of Hyper-V`
click close and restart

on reboot run docker, skip account creation

run `docker run hello-world`   <!-- # for verification -->

To verify docker is working well open terminal and run `docker run hello-world`. It should pull an image then show a message confirming success. 

Open terminal and run `docker pull codewithlennylen/rdj-2024` It will download a large image file (~2GB) that contains ROS2 humble and dependencies


Once finished, go to images tab. Press the play icon on the `codewithlennylen/rdj-2024` image
an image should be created and run.

<!-- docker run -it --name rdj-2024 --privileged --network host --env DISPLAY=$DISPLAY codewithlennylen rdj-2024 -->

launch Xlaunch.exe app
choose multiple windows, click next
choose no client, click next
leave defaults (clipboard, Primary Selection, Native opengl), click next
click save configuration, choose a convenient directory like Desktop
Click finish


launch docker desktop
open terminal and run `ipconfig` and look for the `Ethernet adapter vEthernet (WSL)`
copy the ipv4 address e.g. 172.30.176.1
start the container and run `sudo su`
then run `nano ~/.bashrc`
then paste the following line at the **end** of the file `export DISPLAY=<your ip>:0.0` 
an example is `export DISPLAY=172.30.176.1:0.0`. Press Ctrl+S then Ctrl+X

go to containers tab and click your current container
click files tab and wait for it to load. It may say error, but don't mind, go to exec tab and back to files tab. Then right-click the /home/rdj, click import, select the directory of the workspace

cd into src then `./init.bash`

Then `colcon build --symlink-install` and rebuild then `source install/setup.bash`
 `apt get update`

run `ros2 run demo_nodes_cpp talker` and in another terminal run `ros2 run demo_nodes_cpp listener` and in another run `rqt_graph`. Once done close with Ctrl+C

run `ros2 run turtlesim turtlesim_node` and in another terminal run `ros2 run turtlesim turtlesim_node` `ros2 run turtlesim turtle_teleop_key` and in another run `rqt_graph`. Once done close using Ctrl+C



launch the simulation `ros2 launch jkl launch_sim.launch.py use_sim_time:=true world:=./src/jkl/worlds/dojo2024`



