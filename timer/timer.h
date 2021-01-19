#ifndef __ROS_TIMER__
#define __ROS_TIMER__
#include <ros/ros.h> 
#include <stdio.h>
#include <string.h>

namespace timer{
    inline ros::WallTime ros_begin;
    inline ros::WallDuration ros_duration;
    inline std::stringstream output_data;

    extern void real_time_print();
}

#endif