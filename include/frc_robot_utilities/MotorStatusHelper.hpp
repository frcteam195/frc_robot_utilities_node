#pragma once
#include "frc_robot_utilities/BufferedROSMsgHandler.hpp"
#include "ck_ros_base_msgs_node/Motor_Status.h"
#include "ck_ros_base_msgs_node/Motor_Info.h"
#include <map>
#include <mutex>

class MotorStatusHelper
{
public:
    MotorStatusHelper(BufferedROSMsgHandler<ck_ros_base_msgs_node::Motor_Status>& buffered_msg_obj);
    std::map<uint16_t, ck_ros_base_msgs_node::Motor_Info>& get();

private:
    std::map<uint16_t, ck_ros_base_msgs_node::Motor_Info> motor_map;
    BufferedROSMsgHandler<ck_ros_base_msgs_node::Motor_Status>* buf_handler_ptr = NULL;
    std::recursive_mutex motor_lock;
};