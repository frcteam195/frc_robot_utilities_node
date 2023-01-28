#pragma once
#include "frc_robot_utilities/BufferedROSMsgHandler.hpp"
#include "ck_ros_base_msgs_node/Robot_Status.h"
#include <map>
#include <mutex>
#include <string>

enum class Alliance : int
{
    RED = 0,
    BLUE = 1,
    UNKNOWN = 2
};

enum class RobotMode : int
{
    DISABLED = 0,
    TELEOP = 1,
    AUTONOMOUS = 2,
    TEST = 3
};

class RobotStatusHelper
{
public:
    RobotStatusHelper(BufferedROSMsgHandler<ck_ros_base_msgs_node::Robot_Status>& buffered_msg_obj);

    RobotMode get_mode();
    Alliance get_alliance();
    double get_match_time();
    std::string get_game_data();
    int get_selected_auto();
    bool is_connected();

private:
    BufferedROSMsgHandler<ck_ros_base_msgs_node::Robot_Status>* buf_handler_ptr = NULL;
    std::recursive_mutex robot_lock;

    void update();

    RobotMode robot_state {RobotMode::DISABLED};
    Alliance alliance {Alliance::UNKNOWN};
    double match_time = 0;
    std::string game_data = "";
    int selected_auto = 0;
    bool m_is_connected = false;
};