#pragma once
#include "frc_robot_utilities/BufferedROSMsgHandler.hpp"
#include "rio_control_node/Motor_Status.h"
#include "rio_control_node/Motor_Info.h"
#include <map>
#include <mutex>

class MotorStatusHelper
{
public:
    MotorStatusHelper(BufferedROSMsgHandler<rio_control_node::Motor_Status>& buffered_msg_obj);
    std::map<uint16_t, rio_control_node::Motor_Info>& get();

private:
    std::map<uint16_t, rio_control_node::Motor_Info> motor_map;
    BufferedROSMsgHandler<rio_control_node::Motor_Status>* buf_handler_ptr = NULL;
    std::recursive_mutex motor_lock;
};