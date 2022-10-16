#include <frc_robot_utilities/frc_robot_utilities.hpp>
#include "ros/ros.h"
#include "std_msgs/String.h"

#include <thread>
#include <string>
#include <mutex>

BufferedROSMsgHandler<hmi_agent_node::HMI_Signals> hmi_updates;
BufferedROSMsgHandler<rio_control_node::Robot_Status> robot_updates;
BufferedROSMsgHandler<rio_control_node::Motor_Status> motor_updates_internal;
MotorStatusHelper motor_updates(motor_updates_internal);

void register_for_robot_updates(ros::NodeHandle* node)
{
	hmi_updates.register_for_updates(node, "/HMISignals");
	robot_updates.register_for_updates(node, "/RobotStatus");
	motor_updates_internal.register_for_updates(node, "/MotorStatus");
}