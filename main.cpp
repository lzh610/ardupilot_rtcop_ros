#include <ros/ros.h>
#include "Generated/API.h"
#include "Generated/BaseLayer.h"
//#include "parameter.h"
#include "gnc_functions.h"
#include "test.h"
#include "ActiveController.h"

// std::vector<gnc_api_waypoint> waypointlist;
// gnc_api_waypoint nextWayPoint;
using namespace gnc;
using namespace PLAM;
int main(int argc, char **argv) {
// initialize ros
//   ros::init(argc, argv, "hello");
//   ros::NodeHandle nh; 
	printf("%d",gnc::a_test());
    ros::init(argc, argv, "gnc_node");
	ros::NodeHandle gnc_node;           
    ros::Rate rate(1); 
	
	init_publisher_subscriber(gnc_node);

    // wait for FCU connection
	wait4connect();

	//wait for used to switch to mode GUIDED
	wait4start();

	//create local reference frame 
	initialize_local_frame();            

  	// initialize rtcop
  	RTCOP::Framework::Instance->Initialize();

	// instantiate class Hello
	baselayer::Hello* hello = RTCOP::copnew<baselayer::Hello>();

	std::vector<gnc_api_waypoint> waypointlist;
	gnc_api_waypoint nextWayPoint;
  	//ROS_INFO_STREAM("Hello World!");
  	rate.sleep();                   

	// activate EnglishLayer
	// RTCOP::activate(RTCOP::Generated::LayerID::Ground);
	active_normal(RTCOP::Generated::LayerID::Ground);
	hello->Print();
  	rate.sleep();                   

	// activate JapaneseLayer
	RTCOP::deactivate(RTCOP::Generated::LayerID::Ground);
	RTCOP::activate(RTCOP::Generated::LayerID::Flight);
	hello->Print();
  	rate.sleep();                   
	while (ros::ok())
	{
		/* code */
	}
	
	// Helloのdelete
	delete hello;

	// RTCOPの終了処理
	RTCOP::Framework::Instance->Finalize();
}