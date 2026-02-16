#include <chrono>
#include <functional>
#include <memory>
#include <string>

#include "rclcpp/rclcpp.hpp"

using namespace std::chrono_literals;

/*
 * TODO: Create a Class named 'ParamNode' that inherits from rclcpp::Node.
 * Requirements:
 * 1. The constructor should name the node "param_node".
 * 2. Declare these parameters with default values:
 * - "robot_name" (string): default "ROS2Bot"
 * - "max_speed" (double): default 1.5
 * - "enabled" (bool): default true
 * 3. Create a timer that triggers every 2000ms.
 * 4. In timer callback, read parameters and log:
 * "Robot: <name>, Max Speed: <speed>, Enabled: <enabled>"
 */

class ParamNode : public rclcpp::Node
{
public:
    ParamNode()
        : Node("param_node")
    {
        // TODO: Declare parameters here
        this->declare_parameter("robot_name", "ROS2Bot");
        this->declare_parameter("max_speed", 1.5);
        this->declare_parameter("enabled", true);

        // TODO: Create timer here
        timer_ = this->create_wall_timer(
            2000ms, std::bind(&ParamNode::timer_callback, this));
    }

private:
    // TODO: Define timer_callback function here
    void timer_callback()
    {
        std::string robot_name = this->get_parameter("robot_name").as_string();
        double max_speed = this->get_parameter("max_speed").as_double();
        bool enabled = this->get_parameter("enabled").as_bool();

        RCLCPP_INFO(this->get_logger(), "Robot: %s, Max Speed: %f, Enabled: %s", 
                    robot_name.c_str(), max_speed, enabled ? "true" : "false");
    }

    rclcpp::TimerBase::SharedPtr timer_;
};

int main(int argc, char *argv[])
{
    rclcpp::init(argc, argv);
    rclcpp::spin(std::make_shared<ParamNode>());
    rclcpp::shutdown();
    return 0;
}