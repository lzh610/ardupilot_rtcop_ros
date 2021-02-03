#include "timer.h"


namespace timer{
void real_time_print(){
    ros_duration = ros::WallTime::now() - ros_begin;
	ROS_INFO("[ROS_timer]: %f", ros_duration.toSec()); 
    //output_data << ros_duration.toSec() << ",";
}

}