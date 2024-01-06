#include <ros/ros.h>
#include <actionlib/server/simple_action_server.h>
#include <mastering_ros_demo_pkg/Demo_actionAction.h> // Gantilah 'your_package_name' dengan nama paket Anda

class DemoActionServer {
protected:
    ros::NodeHandle nh_;
    actionlib::SimpleActionServer<mastering_ros_demo_pkg::Demo_actionAction> as_; // Action server
    std::string action_name_;
    mastering_ros_demo_pkg::Demo_actionFeedback feedback_;
    mastering_ros_demo_pkg::Demo_actionResult result_;

public:
    DemoActionServer(const std::string &name) : 
        as_(nh_, name, boost::bind(&DemoActionServer::executeCB, this, _1), false),
        action_name_(name) {
        as_.start(); // Memulai action server
    }

    ~DemoActionServer(void) {}

    // Callback function yang akan dijalankan saat action server menerima goal
    void executeCB(const mastering_ros_demo_pkg::Demo_actionGoalConstPtr &goal) {
        ros::Rate r(1); // Timer dengan delay 1 detik
        bool success = true;

        ROS_INFO("%s: Menerima goal %d", action_name_.c_str(), goal->count);

        for (int i = 0; i <= goal->count; i++) {
            if (as_.isPreemptRequested() || !ros::ok()) {
                ROS_INFO("%s: Goal dibatalkan", action_name_.c_str());
                as_.setPreempted();
                success = false;
                break;
            }

            feedback_.current_number = i; // Mengatur feedback
            as_.publishFeedback(feedback_); // Mengirim feedback

            r.sleep(); // Menunggu 1 detik
        }

        if (success) {
            result_.final_count = feedback_.current_number; // Mengatur hasil
            ROS_INFO("%s: Selesai, mengirimkan hasil", action_name_.c_str());
            as_.setSucceeded(result_); // Mengatur status action server sebagai succeeded
        }
    }
};

int main(int argc, char **argv) {
    ros::init(argc, argv, "demo_action_server"); // Inisialisasi node dengan nama 'demo_action_server'

    DemoActionServer server("demo_action"); // Membuat instance dari DemoActionServer

    ros::spin(); // Loop ROS

    return 0;
}

