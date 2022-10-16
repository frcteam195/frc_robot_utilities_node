#include "ros/ros.h"
#include "hmi_utilities/hmi_utilities.hpp"
#include <mutex>
#include <atomic>

hmi_agent_node::HMI_Signals hmi_signals_update_tmp;
hmi_agent_node::HMI_Signals hmi_signals_buf;
std::recursive_mutex hmi_signals_lock;
std::atomic_bool update_occurred {false};

void hmi_update_func(hmi_agent_node::HMI_Signals hmi_callback_msg)
{
	std::lock_guard<std::recursive_mutex> lock(hmi_signals_lock);
	hmi_signals_update_tmp = hmi_callback_msg;
	update_occurred = true;
}

void register_for_hmi_updates(ros::NodeHandle* node)
{
	ros::Subscriber joystickStatus = node->subscribe("/HMISignals", 1, hmi_update_func, ros::TransportHints().tcpNoDelay());
}

const hmi_agent_node::HMI_Signals& hmi_signals()
{
	if (update_occurred)
	{
		std::lock_guard<std::recursive_mutex> lock(hmi_signals_lock);
		hmi_signals_buf = hmi_signals_update_tmp;
		update_occurred = false;
	}
	return hmi_signals_buf;
}