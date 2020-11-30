#include <ros/ros.h>
#include "Generated/API.h"
#include "Generated/BaseLayer.h"
#include "gnc_functions.h"
#include "ActiveController.h"
#include "string.h"

using namespace gnc;
using namespace PLAM;

ros::Publisher pub;
ros::Subscriber sub;

void chatterCallback(const std_msgs::String::ConstPtr& msg){
    ROS_INFO("I heard:[%s]", msg->data.c_str());
    std_msgs::String return_msg;
    std::stringstream ss;
    ss<< msg->data.c_str() << "_ok";
    return_msg.data = ss.str();

    pub.publish(return_msg);
    ros::spinOnce();
    ROS_INFO("%s", return_msg.data.c_str());
}

int main(int argc, char **argv){
    RTCOP::Framework::Instance->Initialize();
    ros::init(argc,argv,"ground_node");
    ros::NodeHandle ground_node;
    pub = ground_node.advertise<std_msgs::String>("chatter2",1000);
    sub = ground_node.subscribe("chatter", 1000, chatterCallback);
    ros::spin();
    return 0;
}