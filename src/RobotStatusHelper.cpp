#include "frc_robot_utilities/RobotStatusHelper.hpp"

RobotStatusHelper::RobotStatusHelper(BufferedROSMsgHandler<rio_control_node::Robot_Status>& buffered_msg_obj)
{
    buf_handler_ptr = &buffered_msg_obj;
}

void RobotStatusHelper::update()
{
    if (buf_handler_ptr->has_updated())
    {
        std::lock_guard<std::recursive_mutex> lock(robot_lock);
        const rio_control_node::Robot_Status& r_stat = buf_handler_ptr->get();
        robot_state = (RobotMode) r_stat.robot_state;
        alliance = (Alliance) r_stat.alliance;
        match_time = r_stat.match_time;
        game_data = r_stat.game_data;
        selected_auto = r_stat.selected_auto;
    }
}

RobotMode RobotStatusHelper::get_mode()
{
    update();
    return robot_state;
}

Alliance RobotStatusHelper::get_alliance()
{
    update();
    return alliance;
}

double RobotStatusHelper::get_match_time()
{
    update();
    return match_time;
}

std::string RobotStatusHelper::get_game_data()
{
    update();
    return game_data;
}

int RobotStatusHelper::get_selected_auto()
{
    update();
    return selected_auto;
}