#include "ros/ros.h"
#include "mastering_ros_demo_pkg/demo_srv.h"

bool demo_service_callback(mastering_ros_demo_pkg::demo_srv::Request &req,
                           mastering_ros_demo_pkg::demo_srv::Response &res)
{
    ROS_INFO("Received request from client with message: %s", req.in.c_str());
    
    // Di sini Anda bisa menangani permintaan dan menyiapkan respons
    res.out = "Response from server: Server received your message.";

    return true; // Mengembalikan true jika layanan berhasil diproses
}

int main(int argc, char **argv)
{
    ros::init(argc, argv, "demo_service_server");
    ros::NodeHandle n;

    // Membuat server layanan dengan nama "demo_service"
    ros::ServiceServer service = n.advertiseService("demo_service", demo_service_callback);

    ROS_INFO("Ready to receive client requests.");

    ros::spin(); // Tetap berjalan dan menunggu permintaan layanan

    return 0;
}

