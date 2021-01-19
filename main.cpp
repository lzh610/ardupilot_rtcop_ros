#include <ros/ros.h>
#include "Generated/API.h"
#include "Generated/BaseLayer.h"
#include "gnc_functions.h"
#include "ActiveController.h"
#include "ardupilot_rtcop_ros/activation_msg.h"
#include "timer.h"
#include <iostream>
#include <fstream>

using namespace gnc;
using namespace PLAM;
using namespace timer;

//Client
ros::ServiceClient client_ground;
ros::ServiceClient client_flight;
ros::ServiceClient client_nosignal;
ros::ServiceClient client_strongwind;
ros::ServiceClient client_storm;
ros::ServiceClient client_lowpower;
ros::ServiceClient client_nopower;

//レイヤコントロールノードのサーバーコールの受信
ardupilot_rtcop_ros::activation_msg srv_ground;
ardupilot_rtcop_ros::activation_msg srv_flight;
ardupilot_rtcop_ros::activation_msg srv_nosignal;
ardupilot_rtcop_ros::activation_msg srv_strongwind;
ardupilot_rtcop_ros::activation_msg srv_storm;
ardupilot_rtcop_ros::activation_msg srv_lowpower;
ardupilot_rtcop_ros::activation_msg srv_nopower;

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

		else if(strcmp(this_srv.response.activation_return.c_str(),"strongwind_activate_ok") == 0)
		{
			active_suspend_until_deactive(RTCOP::Generated::LayerID::StrongWind);
		}
		else if(strcmp(this_srv.response.activation_return.c_str(),"strongwind_deactivate_ok") == 0)
		{ 
			deactive_suspend(RTCOP::Generated::LayerID::StrongWind);
		}
		else if(strcmp(this_srv.response.activation_return.c_str(),"storm_activate_ok") == 0)
		{ 
			active_break(RTCOP::Generated::LayerID::Storm);
		}
		else if(strcmp(this_srv.response.activation_return.c_str(),"storm_deactivate_ok") == 0)
		{ 
			deactive_normal(RTCOP::Generated::LayerID::Storm);
		}

		else if(strcmp(this_srv.response.activation_return.c_str(),"lowpower_activate_ok") == 0)
		{
			active_suspend(RTCOP::Generated::LayerID::LowPower);
		}
		else if(strcmp(this_srv.response.activation_return.c_str(),"lowpower_deactivate_ok") == 0)
		{ 
			deactive_normal(RTCOP::Generated::LayerID::LowPower);
		}
		else if(strcmp(this_srv.response.activation_return.c_str(),"nopower_activate_ok") == 0)
		{ 
			active_break(RTCOP::Generated::LayerID::NoPower);
		}
		else if(strcmp(this_srv.response.activation_return.c_str(),"nopower_deactivate_ok") == 0)
		{ 
			deactive_normal(RTCOP::Generated::LayerID::NoPower);
		}		
		
		
	}
	else{
		ROS_ERROR("Failed to call service");
	}
}

void waiting(){
	// 目標地点に到達するまでシナリオノードの待機命令
	while(ros::ok()){
		ros::spinOnce();
		//rate.sleep()
		int flag = check_waypoint_reached();
		// ROS_INFO("check point:%d",flag);
		if (flag == 1)
		{
			break;
		}
		sleep(3);	
	}
}

// 外部ファイルに時間データを書き込むこと。シナリオ完了後で実行する
void write_data(){
	ofstream outfile;
	//　パスは適当に記入してください
	outfile.open("/home/lzh/catkin_ws/src/ardupilot_rtcop_ros/data/data.csv", ios::out | ios::app);
	if(!outfile){
		ROS_INFO("file rewriting error!!");
		return;
	}
	outfile << output_data.str() << endl;

	outfile.close();

}

int main(int argc, char **argv) {
	//------------ROS・Ardupilotなどの初期化------------
	//initialize ros
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
	client_flight = gnc_node.serviceClient<ardupilot_rtcop_ros::activation_msg>("flight_activation");
	client_nosignal = gnc_node.serviceClient<ardupilot_rtcop_ros::activation_msg>("nosignal_activation");
	client_strongwind = gnc_node.serviceClient<ardupilot_rtcop_ros::activation_msg>("strongwind_activation");
	client_storm = gnc_node.serviceClient<ardupilot_rtcop_ros::activation_msg>("storm_activation");
	client_lowpower = gnc_node.serviceClient<ardupilot_rtcop_ros::activation_msg>("lowpower_activation");
	client_nopower = gnc_node.serviceClient<ardupilot_rtcop_ros::activation_msg>("nopower_activation");

	/* シナリオが開始
	   route A: [0,0] [40,0]　    異常処理：信号途絶
	   route B: [40,0] [0,40]   　異常処理：強風・暴風
	   route C: [0,40] [-40,0]　　異常処理：強風・信号途絶
	   route D: [-40,0] [0,0]　　　異常処理：電池残量低下・更に低下

	   route Aが起動するタイミングを相対時間（理論的）０sと仮定する。リヤル時間をROS_INFOで表示された時間点から推定できる
	*/

	// route A 開始ーーーーーーーーーーーーーーー 0
	//グランドモードを起動
	ros_begin = ros::WallTime::now();
	
	activation_execution("ground_activate", client_ground, srv_ground);
	
	//time keeper
	real_time_print();

	sleep(1);
	hello->Print();//ここでGround Modeをアウトプットとする
	sleep(2);

	activation_execution("ground_deactivate", client_ground, srv_ground);

	sleep(1);
	hello->Print();//ここでBaseClassをアウトプットとする 153s

	activation_execution("flight_activate", client_flight, srv_flight);
	hello->Print();//ここでBaseClassをアウトプットとする
	sleep(25);

	ROS_INFO_STREAM("[RTCOP]:No signal found!"); 

	activation_execution("nosignal_activate", client_nosignal, srv_nosignal);

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

	activation_execution("nosignal_deactivate", client_nosignal, srv_nosignal);

	hello->Print(); //Flight modeアクティベーションが完了していないのでbase layerのhelloが表示される
	sleep(70);

	//Flight modeアクティベーションが完了
	hello->Flying(40,0); //
	sleep(3);
	
	waiting(); //
	
	land();

	activation_execution("flight_deactivate", client_flight, srv_flight);

	sleep(35);

	//route A　終了ーーーーーーーーーーーーーーー

	//route B　開始ーーーーーーーーーーーーーーー

	activation_execution("flight_activate", client_flight, srv_flight);

	sleep(70);

	hello->Flying(0,40);

	sleep(3);

	activation_execution("flight_deactivate", client_flight, srv_flight);

	sleep(1);

	activation_execution("strongwind_activate",client_strongwind, srv_strongwind);

	sleep(15);

	hello->Flying(0,40);

	sleep(3);

	activation_execution("strongwind_deactivate",client_strongwind, srv_strongwind);

	sleep(1);

	activation_execution("storm_activate",client_storm, srv_storm);

	sleep(15);

	activation_execution("storm_deactivate",client_storm, srv_storm);

	sleep(1);

	activation_execution("flight_activate", client_flight, srv_flight);

	sleep(70);

	hello->Flying(0,40);

	waiting();

	land();

	activation_execution("flight_deactivate", client_flight, srv_flight);

	sleep(45);

	// route B　終了ーーーーーーーーーーーーーーー

	//route C 開始ーーーーーーーーーーーーーーー

	activation_execution("flight_activate", client_flight, srv_flight);

	sleep(50);

	activation_execution("strongwind_activate", client_strongwind, srv_strongwind);

	sleep(10);

	activation_execution("nosignal_activate", client_nosignal, srv_nosignal);

	sleep(2);

	activation_execution("strongwind_deactivate", client_strongwind, srv_strongwind);

	time_counter = 0;
	while (ros::ok())
	{
		hello->Print();
		sleep(1);
		time_counter++;
		if (time_counter >= 10)
		{
			break;
		}
		
	}

	activation_execution("nosignal_deactivate", client_nosignal, srv_nosignal);

	sleep(3);

	activation_execution("strongwind_activate", client_strongwind, srv_strongwind);

	sleep(10);

	hello->Flying(-20,20);

	sleep(3);

	activation_execution("strongwind_deactivate", client_strongwind, srv_strongwind);

	sleep(50);

	hello->Flying(-40,0);

	waiting();

	land();

	activation_execution("flight_deactivate", client_flight, srv_flight);

	sleep(35);

	// route C 終了ーーーーーーーーーーーーーーー

	// route D 開始ーーーーーーーーーーーーーーー

	activation_execution("flight_activate", client_flight, srv_flight);

	sleep(40);

	activation_execution("lowpower_activate", client_lowpower, srv_lowpower);

	sleep(10);

	hello->Flying(0,0);

	sleep(4);

	activation_execution("lowpower_deactivate", client_lowpower, srv_lowpower);

	activation_execution("nopower_activate", client_nopower, srv_nopower);

	sleep(25);

	time_counter = 0;

	while (ros::ok())
	{
		hello->Print();
		sleep(1);
		time_counter++;
		if (time_counter >= 10)
		{
			break;
		}
		
	}
	
	// route D 終了ーーーーーーーーーーーーーーー

	// Helloのdelete
	delete hello;

	// RTCOPの終了処理
	RTCOP::Framework::Instance->Finalize();

	write_data();


}
