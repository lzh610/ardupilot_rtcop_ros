#ifndef __GNC_FUNCTIONS__
#define __GNC_FUNCTIONS__

#include <mavros_msgs/CommandTOL.h>
#include <mavros_msgs/State.h>
#include <nav_msgs/Odometry.h>
#include <geometry_msgs/Pose.h>
#include <geometry_msgs/PoseStamped.h>
#include <cmath>
#include <math.h>
#include <ros/ros.h>
#include <std_msgs/Float64.h>
#include <std_msgs/String.h>
#include <mavros_msgs/CommandBool.h>
#include <mavros_msgs/SetMode.h>
#include <mavros_msgs/PositionTarget.h>
#include <unistd.h>
#include <vector>
#include <ros/duration.h>
#include <iostream>
#include <string>

struct gnc_api_waypoint{
	float x; ///< distance in x with respect to your reference frame
	float y; ///< distance in y with respect to your reference frame
	float z; ///< distance in z with respect to your reference frame
	float psi; ///< rotation about the third axis of your reference frame
};

namespace gnc{


extern void state_cb(const mavros_msgs::State::ConstPtr& msg);

extern void pose_cb(const nav_msgs::Odometry::ConstPtr& msg);

extern geometry_msgs::Point get_current_location();

extern float get_current_heading();

extern void set_heading(float heading);

extern void set_destination(float x, float y, float z, float psi);

extern int wait4connect();

extern int wait4start();

extern int initialize_local_frame();

extern int arm();

extern int takeoff(float takeoff_alt);

extern int check_waypoint_reached();

extern int set_mode(std::string mode);

extern int land();

extern int init_publisher_subscriber(ros::NodeHandle controlnode);

}

inline std::vector<gnc_api_waypoint> waypointlist;
inline gnc_api_waypoint nextWayPoint;

#endif