#!/bin/bash
gnome-terminal --tab "world start" -- roslaunch iq_sim runway.launch;

sleep 10;

gnome-terminal --tab "sitl start" -- roslaunch iq_sim apm.launch;



