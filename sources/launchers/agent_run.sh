source ../agent/agent/install/setup.bash && \
export ROS_DOMAIN_ID=1 && \
ros2 run macspos main.py -config configs/config.json -params configs/params.json -id $1
