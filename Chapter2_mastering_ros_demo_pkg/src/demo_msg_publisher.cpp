#include "ros/ros.h"
#include "mastering_ros_demo_pkg/demo_msg.h" // Menggunakan definisi pesan kustom Anda

int main(int argc, char **argv)
{
  // Inisialisasi node dengan nama "demo_msg_publisher"
  ros::init(argc, argv, "demo_msg_publisher");

  // Membuat objek NodeHandle
  ros::NodeHandle nh;

  // Membuat publisher untuk topik 'demo_topic' dengan buffer ukuran 1000
  ros::Publisher pub = nh.advertise<mastering_ros_demo_pkg::demo_msg>("demo_topic", 1000);

  // Rate untuk mengatur frekuensi publikasi
  ros::Rate loop_rate(1); // Contoh: publikasi setiap detik

  while (ros::ok())
  {
    // Membuat objek pesan
    mastering_ros_demo_pkg::demo_msg msg;
    msg.greeting = "Hello, ROS!";
    msg.number = 123;

    // Mem-publish pesan
    pub.publish(msg);

    // Memproses callback dan menunggu hingga waktunya
    ros::spinOnce();
    loop_rate.sleep();
  }

  return 0;
}

