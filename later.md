
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

Next run 
```
git clone <repourl here>
```

cd into src then
```
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
```
ros2 run turtlesim turtle_teleop_key
``` 
and in another run 
```
rqt_graph
```
Click the terminal window where `turtle_teleop_key` was launched and press the arrow keys. The robot should move. 

Once done close using Ctrl+C

# Gazebo Demo

launch the simulation 
```
ros2 launch jkl launch_sim.launch.py use_sim_time:=true world:=./src/jkl/worlds/dojo2024
```

# Other Resources
ROS introduction course [here](https://www.youtube.com/watch?v=0aPbWsyENA8&list=PLLSegLrePWgJudpPUof4-nVFHGkB62Izy)
Full robot building guide including simulation [here](https://www.youtube.com/watch?v=OWeLUSzxMsw&list=PLunhqkrRNRhYAffV8JDiFOatQXuU-NnxT)



