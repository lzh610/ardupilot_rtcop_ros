#include <ros/ros.h>
#include "Generated/API.h"
#include "Generated/BaseLayer.h"
#include "gnc_functions.h"
#include "ActiveController.h"
#include "ardupilot_rtcop_ros/activation_msg.h"
#include "timer.h"

using namespace gnc;
using namespace PLAM;
using namespace timer;

//Client
ros::ServiceClient client_ground;

//レイヤコントロールノードのサーバーコールの受信
ardupilot_rtcop_ros::activation_msg srv_ground;

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
	time_sum = 0;
	for(int i = 0;i < 100;i ++){
		ros_begin = ros::Time::now();
		activation_execution("ground_activate", client_ground, srv_ground);
		usleep(100000);
		// ros_begin = ros::Time::now();
		activation_execution("ground_deactivate", client_ground, srv_ground);
		usleep(100000);
	}
	int ave = time_sum/100;
	ROS_INFO("[ROS]:average time: %d", ave);

	// sleep(5);

	delete hello;

	// RTCOPの終了処理
	RTCOP::Framework::Instance->Finalize();




}