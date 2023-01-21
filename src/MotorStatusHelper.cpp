#include "frc_robot_utilities/MotorStatusHelper.hpp"

MotorStatusHelper::MotorStatusHelper(BufferedROSMsgHandler<ck_ros_base_msgs_node::Motor_Status>& buffered_msg_obj)
{
    buf_handler_ptr = &buffered_msg_obj;
}

std::map<uint16_t, ck_ros_base_msgs_node::Motor_Info>& MotorStatusHelper::get()
{
    if (buf_handler_ptr->has_updated())
    {
        std::lock_guard<std::recursive_mutex> lock(motor_lock);
        const ck_ros_base_msgs_node::Motor_Status& m_stat = buf_handler_ptr->get();
        for (ck_ros_base_msgs_node::Motor_Info m_info : m_stat.motors)
        {
            motor_map[m_info.id] = m_info;
        }
    }

    return motor_map;
}