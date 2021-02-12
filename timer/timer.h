#ifndef __ROS_TIMER__
#define __ROS_TIMER__
#include <ros/ros.h> 
#include <stdio.h>
#include <string.h>

namespace timer{
    inline ros::Time ros_begin; //walltimeでリヤル時間を表示する
    inline ros::Duration ros_duration;
    inline std::stringstream output_data; //時間データを記録する
    inline int time_sum; //平均時間を算出

    extern void real_time_print();//タイマー
}

#endif