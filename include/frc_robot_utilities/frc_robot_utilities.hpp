#pragma once
#include "ros/ros.h"
#include <frc_robot_utilities/BufferedROSMsgHandler.hpp>
#include <frc_robot_utilities/MotorStatusHelper.hpp>
#include <frc_robot_utilities/RobotStatusHelper.hpp>


#include <ck_ros_msgs_node/HMI_Signals.h>
#include <ck_ros_base_msgs_node/Motor_Status.h>
#include <ck_ros_base_msgs_node/Robot_Status.h>


extern BufferedROSMsgHandler<ck_ros_msgs_node::HMI_Signals> hmi_updates;
extern RobotStatusHelper robot_status;
extern MotorStatusHelper motor_updates;

void register_for_robot_updates(ros::NodeHandle* node_handle);
bool reset_robot_pose(Alliance alliance, double x_inches=0, double y_inches=0, double heading_degrees=0);