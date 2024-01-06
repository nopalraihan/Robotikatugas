#include <ros/ros.h>
#include <actionlib/client/simple_action_client.h>
#include <actionlib/client/terminal_state.h>
#include <mastering_ros_demo_pkg/Demo_actionAction.h> // Gantilah 'your_package_name' dengan nama paket Anda

int main(int argc, char **argv) {
    ros::init(argc, argv, "demo_action_client"); // Inisialisasi node dengan nama 'demo_action_client'
    
    // Membuat instance dari SimpleActionClient dengan tipe action yang sesuai
    actionlib::SimpleActionClient<mastering_ros_demo_pkg::Demo_actionAction> ac("demo_action", true);
    
    ROS_INFO("Menunggu server...");
    ac.waitForServer(); // Menunggu hingga action server tersedia
    
    ROS_INFO("Server ditemukan, mengirim goal...");
    
    mastering_ros_demo_pkg::Demo_actionGoal goal; // Membuat goal
    goal.count = 10; // Contoh pengaturan nilai goal
    
    ac.sendGoal(goal); // Mengirim goal ke action server
    
    // Menunggu hingga goal selesai dengan timeout 30 detik
    bool finished_before_timeout = ac.waitForResult(ros::Duration(30.0));
    
    if (finished_before_timeout) {
        actionlib::SimpleClientGoalState state = ac.getState();
        ROS_INFO("Selesai: %s", state.toString().c_str());
    } else {
        ROS_INFO("Waktu habis, membatalkan goal...");
        ac.cancelGoal(); // Membatalkan goal jika waktu habis
    }
    
    return 0;
}

