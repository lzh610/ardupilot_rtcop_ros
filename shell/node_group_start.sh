#!/bin/bash
gnome-terminal --window "plugin" -- ./plugin.sh;

sleep 10;

gnome-terminal --tab "node_group" -- roslaunch ardupilot_rtcop_ros node_group.launch

sleep 1;

gnome-terminal --tab "sitl start" -- ./startsitl.sh;
