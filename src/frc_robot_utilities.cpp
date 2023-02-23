#include <frc_robot_utilities/frc_robot_utilities.hpp>
#include "ros/ros.h"
#include "std_msgs/String.h"
#include <geometry_msgs/PoseStamped.h>
#include <geometry_msgs/PoseWithCovarianceStamped.h>
#include <robot_localization/SetPose.h>
#include <tf2/LinearMath/Quaternion.h>

#include <thread>
#include <string>
#include <mutex>

BufferedROSMsgHandler<ck_ros_msgs_node::HMI_Signals> hmi_updates;
BufferedROSMsgHandler<ck_ros_base_msgs_node::Robot_Status> robot_updates_internal;
RobotStatusHelper robot_status(robot_updates_internal);
BufferedROSMsgHandler<ck_ros_base_msgs_node::Motor_Status> motor_updates_internal;
MotorStatusHelper motor_updates(motor_updates_internal);

ros::ServiceClient __set_pose_client;
ros::NodeHandle* node;

inline double __deg2rad(double deg)
{
	return deg * M_PI / 180.0;
}

inline double __inches_to_meters(double inches)
{
	return inches * 0.0254;
}

ros::ServiceClient& __set_pose_srv_get()
{
	if (node && !__set_pose_client)
	{
		__set_pose_client = node->serviceClient<robot_localization::SetPose>("/set_pose", true);
	}
	return __set_pose_client;
}

void register_for_robot_updates(ros::NodeHandle* node_handle)
{
	node = node_handle;
	hmi_updates.register_for_updates(node, "/HMISignals");
	robot_updates_internal.register_for_updates(node, "/RobotStatus");
	motor_updates_internal.register_for_updates(node, "/MotorStatus");
	(void)__set_pose_srv_get();
}

bool reset_robot_pose(Alliance alliance, double x_inches, double y_inches, double heading_degrees)
{    
	if (node)
	{
		robot_localization::SetPose initial_pose;
		initial_pose.request.pose.header.stamp = ros::Time::now();
		initial_pose.request.pose.header.frame_id = "odom";

		initial_pose.request.pose.pose.pose.position.x = __inches_to_meters(x_inches);
		initial_pose.request.pose.pose.pose.position.y = __inches_to_meters(y_inches);
		initial_pose.request.pose.pose.pose.position.z = 0;

		double heading_rad = __deg2rad(heading_degrees);
		if (alliance == Alliance::BLUE)
		{
        	heading_rad += M_PI;
		}

		tf2::Quaternion q;
		q.setRPY(0,0,heading_rad);
		initial_pose.request.pose.pose.pose.orientation.w = q.getW();
		initial_pose.request.pose.pose.pose.orientation.x = q.getX();
		initial_pose.request.pose.pose.pose.orientation.y = q.getY();
		initial_pose.request.pose.pose.pose.orientation.z = q.getZ();

		initial_pose.request.pose.pose.covariance =
		{ 0.01, 0.0, 0.0, 0.0, 0.0, 0.0,
			0.0, 0.01, 0.0, 0.0, 0.0, 0.0,
			0.0, 0.0, 0.01, 0.0, 0.0, 0.0,
			0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
			0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
			0.0, 0.0, 0.0, 0.0, 0.0, 0.0174533,};

		ros::ServiceClient pos_reset_service = __set_pose_srv_get();
		if(pos_reset_service && pos_reset_service.call(initial_pose))
		{
			ROS_INFO ("Resetting robot pose to %s", initial_pose.request.pose.header.frame_id.c_str());
			return true;
		}
		else
		{
			ROS_ERROR("FAILED TO RESET ROBOT POSE!");
			return false;
		}
	}
	ROS_ERROR("NODE HANDLE NOT INITIALIZED!");
	return false;
}