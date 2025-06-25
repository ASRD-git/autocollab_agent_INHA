FROM ubuntu:22.04

# Turn y/n interrupts off
ENV DEBIAN_FRONTEND=noninteractive

### basic setup ###
RUN \
apt update  -y && \
apt upgrade -y && \
apt install -y nano && \
apt install -y vim && \
apt install -y git && \
apt install -y curl

### python setup ###
RUN \
apt install -y python3-pip

RUN \
    pip3 install numpy           && \
    pip3 install matplotlib      && \
    pip3 install cvxpy           && \
    pip3 install scipy           && \
    pip3 install asyncio         && \
    pip3 install cfclient        && \
    pip3 install jinja2          && \
    pip3 install numpy toml      && \
    pip3 install --user pyros-genmsg


### c++ setup ###
RUN \
apt install libgl1-mesa-glx -y && \
apt install -y libglib2.0-0

RUN \
apt install x11-apps -y && \
apt install libxcb-xinerama0 libxcb-cursor0 -y && \ 
apt install libdc1394-dev libxvidcore-dev libx264-dev -y && \
apt install libxine2-dev libv4l-dev v4l-utils -y && \
apt install libgstreamer1.0-dev libgstreamer-plugins-base1.0-dev -y && \
apt install libgtk-3-dev -y && \
apt install -y cmake g++ wget unzip

### ROS2 setup ###

RUN \
    apt update && apt install -y locales && \
    locale-gen en_US en_US.UTF-8 && \
    update-locale LC_ALL=en_US.UTF-8 LANG=en_US.UTF-8 && \
    export LANG=en_US.UTF-8

RUN \
    apt install -y software-properties-common && \
    add-apt-repository universe

RUN \
    apt update && \
    curl -sSL https://raw.githubusercontent.com/ros/rosdistro/master/ros.key -o /usr/share/keyrings/ros-archive-keyring.gpg

RUN \
    echo "deb [arch=$(dpkg --print-architecture) signed-by=/usr/share/keyrings/ros-archive-keyring.gpg] http://packages.ros.org/ros2/ubuntu $(. /etc/os-release && echo $UBUNTU_CODENAME) main" | tee /etc/apt/sources.list.d/ros2.list > /dev/null

RUN \
    apt update && \
    apt upgrade && \
    apt install -y ros-humble-desktop

### install ros2 dependencies ###
RUN \
    apt install -y python3-colcon-common-extensions && \
    apt install -y python3-rosdep && \
    apt install -y python3-argcomplete && \
    apt install -y python3-vcstool && \
    apt install -y python3-rosinstall && \
    apt install -y python3-rosinstall-generator && \
    apt install -y python3-wstool

RUN echo "source /opt/ros/humble/setup.bash" >> ~/.bashrc

WORKDIR /home
