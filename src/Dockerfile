FROM ros:humble-ros-base-jammy

# install most of what we need
RUN apt-get update && apt-get install -y --no-install-recommends \
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
    gazebo libgazebo-dev ros-humble-gazebo-ros-pkgs \
    && rm -rf /var/lib/apt/lists/* && apt-get clean


# create a user so that we don't use root all the time
ARG USERNAME=pancake
ARG USER_UID=1000
ARG USER_GID=$USER_UID

RUN groupadd --gid $USER_GID $USERNAME \
    && useradd -s /bin/bash --uid $USER_UID --gid $USER_GID -m $USERNAME \
    && mkdir /home/$USERNAME/.config && chown $USER_UID:$USER_GID /home/$USERNAME/.config

RUN echo $USERNAME ALL=\(root\) NOPASSWD:ALL > /etc/sudoers.d/$USERNAME \
    && chmod 0440 /etc/sudoers.d/$USERNAME

# add the user to dialout group for usb devices
RUN usermod -aG dialout ${USERNAME}

# update bashrc
RUN echo "" >> /home/$USERNAME/.bashrc
RUN echo "source /opt/ros/$ROS_DISTRO/setup.bash" >> /home/$USERNAME/.bashrc

USER $USERNAME
RUN pip3 install wget
USER root
RUN apt-get autoremove -y


ENTRYPOINT ["/bin/bash", "/ros_entrypoint.sh"]
CMD ["bash"]