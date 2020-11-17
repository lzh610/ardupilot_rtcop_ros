#include <ros/ros.h>
#include "Generated/API.h"
#include "Generated/BaseLayer.h"
#include "gnc_functions.h"
#include "ActiveController.h"

using namespace gnc;
using namespace PLAM;

int main(int argc, char **argv) {
	//------------ROS・Ardupilotなどの初期化------------
	// initialize ros
    ros::init(argc, argv, "gnc_node");
	ros::NodeHandle gnc_node;           
    ros::Rate rate(1); 
	
	init_publisher_subscriber(gnc_node);

	ros::Publisher chatter_pub = gnc_node.advertise<std_msgs::String>("chatter",1000);

	// wait for FCU connection
	wait4connect();

	//wait for used to switch to mode GUIDED
	wait4start();

	//create local reference frame 
	initialize_local_frame();            
	//------------ROS・Ardupilotなどの初期化　完了------------
	int count = 0;
  	// while (ros::ok())
  	// {
    // 	/* code */
    // 	std_msgs::String msg;

    // 	std::stringstream ss;

    // 	ss<< "hello world" << count;

    // 	msg.data = ss.str();

    // 	ROS_INFO("%s", msg.data.c_str());

    // 	chatter_pub.publish(msg);

    // 	ros::spinOnce();

    // 	rate.sleep();
    // 	++count;
  	// }

	// initialize rtcop
  	RTCOP::Framework::Instance->Initialize();

	// instantiate class Hello
	baselayer::Hello* hello = RTCOP::copnew<baselayer::Hello>();
	hello->Print();
  	rate.sleep(); 
	
	std_msgs::String msg;

	std::stringstream ss;
	
	//ss<<"hello world!";
	msg.data = "hello world!";
    ROS_INFO("%s", msg.data.c_str());
    chatter_pub.publish(msg);
    ros::spinOnce();
    rate.sleep();

	sleep(5);
	hello->Print();
	//ss.clear();
	//ss<<"ground_activate";
	msg.data = "ground_activate";
    ROS_INFO("%s", msg.data.c_str());
    chatter_pub.publish(msg);
    ros::spinOnce();
    rate.sleep();

	sleep(5);
	hello->Print();
	//ss.clear();
	//ss<<"ground_deactivate";
	msg.data = "ground_deactivate";
    ROS_INFO("%s", msg.data.c_str());
    chatter_pub.publish(msg);
    ros::spinOnce();
    rate.sleep();
	
	sleep(5);
	hello->Print();

}
