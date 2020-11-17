#include <ros/ros.h>
#include "Generated/API.h"
#include "Generated/BaseLayer.h"
#include "gnc_functions.h"
#include "ActiveController.h"
#include "string.h"

using namespace gnc;
using namespace PLAM;

void chatterCallback(const std_msgs::String::ConstPtr& msg){
    ROS_INFO("I heard:[%s]", msg->data.c_str());
    string ground_activate = "ground_activate";
    ROS_INFO("%d", strcmp(msg->data.c_str(),"ground_activate"));
    if(strcmp(msg->data.c_str(),ground_activate.c_str()) == 0){
        //active_normal(RTCOP::Generated::LayerID::Flight);
        RTCOP::activate(RTCOP::Generated::LayerID::Ground);
    }else if(strcmp(msg->data.c_str(),"ground_deactivate") == 0){
        deactive_normal(RTCOP::Generated::LayerID::Ground);
    }
}

int main(int argc, char **argv){
    RTCOP::Framework::Instance->Initialize();
    ros::init(argc,argv,"ground_node");
    ros::NodeHandle ground_node;
    ros::Subscriber sub = ground_node.subscribe("chatter", 1000, chatterCallback);
    ros::spin();
    return 0;
}