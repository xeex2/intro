#!/bin/bash
set -e

# Refresh ROS 2 GPG key (quick fix for expired key)
echo "[INFO] Updating ROS 2 GPG key..."
curl -sSL https://raw.githubusercontent.com/ros/rosdistro/master/ros.asc \
| gpg --dearmor | sudo tee /usr/share/keyrings/ros2-latest-archive-keyring.gpg > /dev/null

sudo apt update

# Install some ROS2 packages
echo "[INFO] Installing dependencies..."
sudo apt install -y \
  ros-humble-ros2-control \
  ros-humble-ros2-controllers \
  ros-humble-gazebo-ros-pkgs  \
  ros-humble-twist-mux \
  ros-humble-teleop-twist-keyboard \
  '~nros-humble-rqt*'
  
# Create workspace and clone EOL gazebo-ros2-control
echo "[INFO] Cloning gazebo_ros2_control..."

git clone -b humble https://github.com/ros-simulation/gazebo_ros2_control.git

# Step 4: Build the workspace
echo "[INFO] Building workspace..."
cd ..
source /opt/ros/humble/setup.bash
colcon build --symlink-install

# Step 5: Source the workspace automatically
echo "source ${PWD}/install/setup.bash" >> ~/.bashrc
source ~/.bashrc
echo "[INFO] Setup complete."
