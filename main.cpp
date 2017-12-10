/*
 * ROS2 demo service server for adding two integers.
 *
 * Refer to https://github.com/ros2/examples/blob/master/rclcpp/minimal_service/main.cpp
 */

#include<cinttypes>
#include<memory>

#include<kfj_ros2_demo_service_interface/srv/add_two_ints.hpp>
#include<rclcpp/rclcpp.hpp>

const static char* g_service_name = "add_two_ints";
/**
 * Class for receiving two integers from the client and sending the sum back.
 */
class DemoServer : public rclcpp::Node
{
public:
    using AddTwoInts = kfj_ros2_demo_service_interface::srv::AddTwoInts;

    DemoServer()
        : Node("DemoServer")
    {
        printf("The server started!\n");
        m_server = create_service<AddTwoInts>(g_service_name,
                &DemoServer::handle_request); // std::bind does not work here for non-static member function
    }

private:
    static void handle_request(
            const std::shared_ptr<rmw_request_id_t> /*request_header_*/,
            const std::shared_ptr<AddTwoInts::Request> request_,
            const std::shared_ptr<AddTwoInts::Response> response_
            )
    {
        int a = request_->a;
        int b = request_->b;
        printf("Received request: a=%d, b=%d\n", a, b);
        response_->sum = a + b;
    }
private:
    rclcpp::service::Service<AddTwoInts>::SharedPtr m_server;
};

int main(int argc, char* argv[])
{
    rclcpp::init(argc, argv);

    auto server = std::make_shared<DemoServer>();
    rclcpp::spin(server);
    rclcpp::shutdown();

    return 0;
}

