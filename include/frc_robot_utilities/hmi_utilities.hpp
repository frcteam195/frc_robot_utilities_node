#pragma once

#include "hmi_agent_node/HMI_Signals.h"

/**
 * @brief Register for hmi data updates. Call once before spin or spin_once
 * @param node The pointer to the instantiated NodeHandle object
*/
void register_for_hmi_updates(ros::NodeHandle* node);

/**
 * @brief Get the latest HMI_Signals data
 * @return The HMI_Signals data
*/
const hmi_agent_node::HMI_Signals& hmi_signals();