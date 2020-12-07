#include <ros/ros.h>
#include "Generated/API.h"
#include "Generated/BaseLayer.h"
#include "gnc_functions.h"
#include "ActiveController.h"
#include "ardupilot_rtcop_ros/activation_msg.h"

using namespace gnc;
using namespace PLAM;

ros::ServiceClient client;
ros::ServiceClient client2;
ros::ServiceClient client3;

ardupilot_rtcop_ros::activation_msg srv;
ardupilot_rtcop_ros::activation_msg srv2;
ardupilot_rtcop_ros::activation_msg srv3;

//簡単なコンテストリースナーを作成しました、カスタマイズで定義できます。
void activation_execution(string request,ros::ServiceClient this_client,ardupilot_rtcop_ros::activation_msg this_srv){
	
	this_srv.request.activation = request;

	if (this_client.call(this_srv))
    {
		ROS_INFO("request: %s", this_srv.response.activation_return.c_str());
		// ROS_INFO("request: %s", srv2.response.activation_return.c_str());
		// ROS_INFO("request: %s", srv3.response.activation_return.c_str()); 
		if(strcmp(this_srv.response.activation_return.c_str(),"ground_activate_ok") == 0){
			active_normal(RTCOP::Generated::LayerID::Ground);
		}
		else if(strcmp(this_srv.response.activation_return.c_str(),"ground_deactivate_ok") == 0)
		{ 
			deactive_normal(RTCOP::Generated::LayerID::Ground);
		}
		else if(strcmp(this_srv.response.activation_return.c_str(),"flight_activate_ok") == 0)
		{
			active_normal(RTCOP::Generated::LayerID::Flight);
		}
		else if(strcmp(this_srv.response.activation_return.c_str(),"flight_deactivate_ok") == 0)
		{ 
			deactive_normal(RTCOP::Generated::LayerID::Flight);
		}
		else if(strcmp(this_srv.response.activation_return.c_str(),"nosignal_activate_ok") == 0)
		{ 
			active_suspend_until_deactive(RTCOP::Generated::LayerID::Nosignal);
		}
		else if(strcmp(this_srv.response.activation_return.c_str(),"nosignal_deactivate_ok") == 0)
		{ 
			deactive_suspend(RTCOP::Generated::LayerID::Nosignal);
		}
		
		
		
	}
	else{
		ROS_ERROR("Failed to call service add_two_ints");
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
	
	client = gnc_node.serviceClient<ardupilot_rtcop_ros::activation_msg>("activation");
	client2 = gnc_node.serviceClient<ardupilot_rtcop_ros::activation_msg>("activation2");
	client3 = gnc_node.serviceClient<ardupilot_rtcop_ros::activation_msg>("activation3");

	activation_execution("ground_activate", client, srv);

	sleep(1);
	hello->Print();
	sleep(2);

	activation_execution("ground_deactivate", client, srv);

	sleep(1);
	hello->Print();

	activation_execution("flight_activate", client2, srv2);
	hello->Print();
	sleep(25);

	ROS_INFO_STREAM("[RTCOP]:No signal found!");

	activation_execution("nosignal_activate", client3, srv3);

	int time_counter = 0;
	while (ros::ok())//一秒ごとでprint関数を実行する
	{
		hello->Print();//Nosignal modeアクティベーションが完了。Nosignal modeのhelloが表示される
		sleep(1);
		time_counter++;
		if (time_counter >= 10)
		{
			break;
		}
		
	}

	activation_execution("nosignal_deactivate", client3, srv3);

	hello->Print(); //Flight modeアクティベーションが完了していないのでbase layerのhelloが表示される
	sleep(70);
	hello->Print(); //Flight modeアクティベーションが完了。Flight modeのhelloが表示される
	// Helloのdelete
	delete hello;

	// RTCOPの終了処理
	RTCOP::Framework::Instance->Finalize();




}
