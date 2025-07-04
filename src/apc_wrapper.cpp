#include <rclcpp/rclcpp.hpp>
#include "apc_camera_component.hpp"
#include <csignal>

void sigintHandler(int /*sig*/){
    rclcpp::shutdown();
}

int main(int argc, char * argv[])
{
    setvbuf(stdout, NULL, _IONBF, BUFSIZ);

    rclcpp::init(argc, argv);

    rclcpp::executors::SingleThreadedExecutor exec;
    rclcpp::NodeOptions options;

    auto dmpreview = std::make_shared<dmpreview::ApcCamera>(options);
    exec.add_node(dmpreview);

    signal(SIGINT, sigintHandler);

    exec.spin();

    std::cout <<"process shutdown ..." <<std::endl;

    rclcpp::shutdown();

    return 0;
}
