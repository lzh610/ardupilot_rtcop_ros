Skip to content
Search or jump to…

Pull requests
Issues
Marketplace
Explore
 
@lzh610 
lzh610
/
ardupilot_rtcop_ros
2
11
Code
Issues
3
Pull requests
1
Actions
Projects
Wiki
Security
Insights
Settings
ardupilot_rtcop_ros/main.cpp
@lzh610
lzh610 add starting shell
Latest commit 24d27a9 on Dec 21, 2020
 History
 1 contributor
141 lines (108 sloc)  4.24 KB
 
#include <ros/ros.h>
#include "Generated/API.h"
#include "Generated/BaseLayer.h"
#include "gnc_functions.h"
#include "ActiveController.h"
#include "ardupilot_rtcop_ros/activation_msg.h"

using namespace gnc;
using namespace PLAM;

//Client
ros::ServiceClient client_ground;
ros::ServiceClient client_flight;
ros::ServiceClient client_nosignal;

//レイヤコントロールノードのサーバーコールの受信
ardupilot_rtcop_ros::activation_msg srv_ground;
ardupilot_rtcop_ros::activation_msg srv_flight;
ardupilot_rtcop_ros::activation_msg srv_nosignal;

//簡単なコンテストリースナーを作成しました、カスタマイズで定義できます。
void activation_execution(string request,ros::ServiceClient this_client,ardupilot_rtcop_ros::activation_msg this_srv){
	
	this_srv.request.activation = request;

	if (this_client.call(this_srv))
    {
		ROS_INFO("request: %s", this_srv.response.activation_return.c_str());
		if(strcmp(this_srv.response.activation_return.c_str(),"ground_activate_ok") == 0){
			active_normal(RTCOP::Generated::LayerID::Ground);
		}
		else if(strcmp(this_srv.response.activation_return.c_str(),"ground_deactivate_ok") == 0)
		{ 
			deactive_normal(RTCOP::Generated::LayerID::Ground);
		}
	}
	else{
		ROS_ERROR("Failed to call service");
	}
}

int main(int argc, char **argv) {
	//------------ROS・Ardupilotなどの初期化------------
	// initialize ros
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
	//------------ROS・Ardupilotなどの初期化　完了------------
	int count = 0;

	// initialize rtcop
  	RTCOP::Framework::Instance->Initialize();

	// instantiate class Hello
	baselayer::Hello* hello = RTCOP::copnew<baselayer::Hello>();
	hello->Print();
  	//rate.sleep(); 
	
	//クライントとサーバーの対応関係を構築
	client_ground = gnc_node.serviceClient<ardupilot_rtcop_ros::activation_msg>("ground_activation");
	// Helloのdelete
	delete hello;

	// RTCOPの終了処理
	RTCOP::Framework::Instance->Finalize();




}