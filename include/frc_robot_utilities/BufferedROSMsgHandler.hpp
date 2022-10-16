#pragma once

#include "ros/ros.h"
#include <string>
#include <mutex>

template <typename T>
class BufferedROSMsgHandler
{
private:
    T msg_update_tmp;
    T msg_buf;
    std::recursive_mutex msg_lock;
    std::atomic_bool update_occurred {false};

    void update_func(const T& callback_msg)
    {
        std::lock_guard<std::recursive_mutex> lock(msg_lock);
        msg_update_tmp = callback_msg;
        update_occurred = true;
    }

public:
    BufferedROSMsgHandler()
    {

    };

    /**
     * @brief Register for hmi data updates. Call once before spin or spin_once
     * @param node The pointer to the instantiated NodeHandle object
     * @param topic The name of the ROS topic to subscribe to
     * @param queue_size The ROS msg queue size. Defaults to 1
    */
    void register_for_updates(ros::NodeHandle* node, std::string topic, int queue_size = 1)
    {
            ros::Subscriber subscriber = node->subscribe(topic, queue_size, &BufferedROSMsgHandler<T>::update_func, this, ros::TransportHints().tcpNoDelay());
    };

    /**
     * @brief Get the latest message data
     * @return The latest ROS msg data that this instance is subscribed to
    */
    const T& get()
    {
        if (update_occurred)
        {
            std::lock_guard<std::recursive_mutex> lock(msg_lock);
            msg_buf = msg_update_tmp;
            update_occurred = false;
        }
        return msg_buf;
    };

    bool has_updated()
    {
        return update_occurred;
    }
};