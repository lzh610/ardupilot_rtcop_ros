#include <ros/ros.h>
#include "Generated/API.h"
#include "Generated/BaseLayer.h"
#include "gnc_functions.h"
#include "ActiveController.h"
#include "string.h"
#include "ardupilot_rtcop_ros/activation_msg.h"

using namespace gnc;
using namespace PLAM;

bool msg_return(ardupilot_rtcop_ros::activation_msg::Request &req,
         ardupilot_rtcop_ros::activation_msg::Response &res)
{
    // テスト版として応答メッセージに"_ok"を追加だけ
    if(strcmp(req.activation.c_str(),"nosignal_activate") == 0 || strcmp(req.activation.c_str(),"nosignal_deactivate") == 0)
        res.activation_return = req.activation + "_ok";
    ROS_INFO("request: %s", res.activation_return.c_str()); 
    return true;
}

int main(int argc, char **argv){
    ros::init(argc,argv,"nosignal_node");
    ros::NodeHandle nosignal_node;
    ros::ServiceServer service = nosignal_node.advertiseService("activation3", msg_return);
    ros::spin();
    return 0;
}