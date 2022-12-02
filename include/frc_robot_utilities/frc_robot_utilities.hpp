#pragma once
#include "ros/ros.h"
#include <frc_robot_utilities/BufferedROSMsgHandler.hpp>
#include <frc_robot_utilities/MotorStatusHelper.hpp>
#include <frc_robot_utilities/RobotStatusHelper.hpp>


#include <hmi_agent_node/HMI_Signals.h>
#include <rio_control_node/Motor_Status.h>
#include <rio_control_node/Robot_Status.h>


extern BufferedROSMsgHandler<hmi_agent_node::HMI_Signals> hmi_updates;
extern RobotStatusHelper robot_status;
extern MotorStatusHelper motor_updates;

void register_for_robot_updates(ros::NodeHandle* node);