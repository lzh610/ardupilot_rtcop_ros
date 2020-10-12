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

    // wait for FCU connection
	wait4connect();

	//wait for used to switch to mode GUIDED
	wait4start();

	//create local reference frame 
	initialize_local_frame();            
	//------------ROS・Ardupilotなどの初期化　完了------------
  	
	// initialize rtcop
  	RTCOP::Framework::Instance->Initialize();

	// instantiate class Hello
	baselayer::Hello* hello = RTCOP::copnew<baselayer::Hello>();
	hello->Print();
  	rate.sleep();                   
	// Ground Mode 起動
	active_normal(RTCOP::Generated::LayerID::Ground);
	hello->Print();
  	rate.sleep();                   
	sleep(3);

	// Ground Mode 解除（PLAMにおける正常系deactivate関数をちょっとBUGが発見したため、もうちょっと修正します）
	RTCOP::deactivate(RTCOP::Generated::LayerID::Ground);
	// Flight Mode　起動
	active_normal(RTCOP::Generated::LayerID::Flight);
	hello->Print();
	sleep(25);

	//信号途絶が発生
	ROS_INFO_STREAM("[RTCOP]:No signal found!");

	//Nosignal Mode 起動
	active_suspend_until_deactive(RTCOP::Generated::LayerID::Nosignal);

	int time_counter = 0;
	while (ros::ok())//一秒ごとでprint関数を実行する
	{
		hello->Print();
		sleep(1);
		time_counter++;
		if (time_counter >= 10)
		{
			break;
		}
		
	}

	//再接続成功、Nosignal Mode 解除
	deactive_suspend(RTCOP::Generated::LayerID::Nosignal);                   
	hello->Print();
	sleep(70);
	hello->Print();
	// Helloのdelete
	delete hello;

	// RTCOPの終了処理
	RTCOP::Framework::Instance->Finalize();
}