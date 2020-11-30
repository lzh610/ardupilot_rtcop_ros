#include <ros/ros.h>
#include "Generated/API.h"
#include "Generated/BaseLayer.h"
#include "gnc_functions.h"
#include "ActiveController.h"

using namespace gnc;
using namespace PLAM;

ros::Publisher pub;
ros::Subscriber sub;

void return_msg(const std_msgs::String::ConstPtr& msg){
    ROS_INFO("I heard:[%s]", msg->data.c_str());
    //ros::spinOnce();
	string ground_activate = "ground_activate_ok";
	if(strcmp(msg->data.c_str(),ground_activate.c_str()) == 0){
        //active_normal(RTCOP::Generated::LayerID::Flight);
        active_normal(RTCOP::Generated::LayerID::Ground);
    }else if(strcmp(msg->data.c_str(),"ground_deactivate_ok") == 0){
        deactive_normal(RTCOP::Generated::LayerID::Ground);
    }
	//ros::spinOnce();
}

int main(int argc, char **argv) {
	//------------ROS・Ardupilotなどの初期化------------
	// initialize ros
    ros::init(argc, argv, "gnc_node");
	ros::NodeHandle gnc_node;           
    ros::Rate rate(1); 
	
	init_publisher_subscriber(gnc_node);

	pub = gnc_node.advertise<std_msgs::String>("chatter",1000);
	sub = gnc_node.subscribe("chatter2", 1000, return_msg);

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
	
	std_msgs::String msg;

	std::stringstream ss;

	msg.data = "initial message";
	
	//メッセージ隊列を安定させるため初期化メッセージを入隊させ
	for(int i = 0;i < 10;i ++){
    	ROS_INFO("%s", msg.data.c_str());
    	pub.publish(msg);
    	ros::spinOnce();
    	//rate.sleep();
		sleep(1);
	}
	
	sleep(5);
	
	//-----------------グランドレイヤーをアクティベート
	msg.data = "ground_activate";
    ROS_INFO("%s", msg.data.c_str());
    pub.publish(msg);
    ros::spinOnce();

	//********ground_nodeの応答と同期化するため、後回して任意のメッセージ（アクティベート関連なし）を入隊させる
	sleep(1);
	msg.data = "over";
    pub.publish(msg);
    ros::spinOnce();
	//***********************

	sleep(5);
	hello->Print();
	
	//--------------------グランドレイヤーをデアクティベート
	msg.data = "ground_deactivate";
    ROS_INFO("%s", msg.data.c_str());
    pub.publish(msg);
    ros::spinOnce();

	sleep(1);
	msg.data = "over";
    pub.publish(msg);
    ros::spinOnce();
	
	sleep(5);
	hello->Print();
}
