#!/bin/bash
gnome-terminal --tab "world start" -- roslaunch ardupilot_rtcop_ros runway_test.launch;

sleep 10;

gnome-terminal --tab "sitl start" -- roslaunch iq_sim apm.launch;



