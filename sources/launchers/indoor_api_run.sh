source ../indoor_interface/install/setup.bash && \
export ROS_DOMAIN_ID=1 && \
ros2 run qcf_interface main.py -config configs/config.json -id $1
