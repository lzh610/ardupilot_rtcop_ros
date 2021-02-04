#include "timer.h"


namespace timer{
void real_time_print(){
    ros_duration = ros::WallTime::now() - ros_begin;
	ROS_INFO("[ROS_timer]: %u", ros_duration.nsec); 
    //output_data << ros_duration.toSec() << ",";
}

}