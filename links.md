download and install VcXsrv (~50MB) https://sourceforge.net/projects/vcxsrv/
download and install realvnc () https://downloads.realvnc.com/
download and install WSL (~300MB) https://github.com/microsoft/WSL/releases/download/2.5.9/wsl.2.5.9.0.x64.msi
download and install docker desktop (~600MB) https://docs.docker.com/desktop/
make sure you check `Use WSL 2 instead of Hyper-V`
click close and restart

on reboot run docker, skip account creation


ignore these
[Remove necessity for sudo command](https://docs.docker.com/engine/install/linux-postinstall/#manage-docker-as-a-non-root-user)

* sudo groupadd docker
* sudo usermod -aG docker $USER
* log out then log back in
* docker run hello-world   <!-- # for verification -->

To verify docker it working well Open terminal and run `docker run hello-world`. It should show a message confirming success. 

Open terminal and run `docker pull codewithlennylen/rdj-2024` It will download a large image file (~2GB) that contains ROS2 etc. prepackaged

Once finished, go to images tab. Press the play icon on the `codewithlennylen/rdj-2024` image
an image should be created and run.

ignore this
git clone https://github.com/roboticsdojo/rdj-2024-docker.git
cd rdj-2024-docker
chmod +x start-rdj-2024.sh
./start-rdj-2024.sh


<!-- docker run -it --name rdj-2024 --privileged --network host --env DISPLAY=$DISPLAY codewithlennylen rdj-2024 -->

change to `nat` network in wsl settings app
reboot to apply changes
launch docker desktop
open terminal and run `ipconfig` and look for the `Ethernet adapter vEthernet (WSL)`
copy the ipv4 address e.g. 172.30.176.1
start the container and run `sudo su`
then run `nano ~/.bashrc`
then paste the following line at the **end** of the file `export DISPLAY=<your ip>:0.0` 
an example is `export DISPLAY=172.30.176.1:0.0`. Press Ctrl+S then Ctrl+X

go to containers tab and click your current container
click files tab and wait for it to load. It may say error, but don't mind, go to exec tab and back to files tab. Then right-click the /home/rdj, click import, select the directory of the workspace

To fix GPG key error `curl -sSL https://raw.githubusercontent.com/ros/rosdistro/master/ros.asc | gpg --dearmor | sudo tee /usr/share/keyrings/ros2-latest-archive-keyring.gpg > /dev/null && sudo apt update`

cd into the directory then `colcon build --symlink-install` and rebuild then `source install/setup.bash`
 `apt get update`
install twist mux `apt install ros-humble-twist-mux`
`sudo apt install '~nros-humble-rqt*'`

launch the simulation `ros2 launch jkl launch_sim.launch.py use_sim_time:=true world:=./src/jkl/worlds/dojo2024`



