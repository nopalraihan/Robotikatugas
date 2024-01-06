#include "ros/ros.h"
#include "mastering_ros_demo_pkg/demo_msg.h" // Menggunakan definisi pesan kustom Anda

// Fungsi callback untuk pesan yang diterima
void msgCallback(const mastering_ros_demo_pkg::demo_msg::ConstPtr& msg)
{
  ROS_INFO("Received Greeting: %s", msg->greeting.c_str());
  ROS_INFO("Received Number: %d", msg->number);
}

int main(int argc, char **argv)
{
  // Inisialisasi node dengan nama "demo_msg_subscriber"
  ros::init(argc, argv, "demo_msg_subscriber");

  // Membuat objek NodeHandle
  ros::NodeHandle nh;

  // Membuat subscriber untuk topik 'demo_topic' dengan buffer ukuran 1000 dan menghubungkannya ke fungsi callback
  ros::Subscriber sub = nh.subscribe("demo_topic", 1000, msgCallback);

  // Memproses callback
  ros::spin();

  return 0;
}

