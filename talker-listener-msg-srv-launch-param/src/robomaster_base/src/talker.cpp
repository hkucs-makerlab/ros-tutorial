#include <sstream>

#include "robomaster_msg/Num.h"
#include "ros/ros.h"
#include "std_msgs/String.h"


int main(int argc, char **argv) {
  ros::init(argc, argv, "talker");

  ros::NodeHandle n("~"); // using private name space

  int freq;
  n.param("loop_rate",freq,10); 
  ROS_INFO("freq for loop rate is %d",freq);
  ros::Rate loop_rate(freq);

  ros::Publisher chatter_pub = n.advertise<std_msgs::String>("chatter", 1000);
  ros::Publisher chatter_num_pub = n.advertise<robomaster_msg::Num>("chatter_num", 1000);

  int count = 0;
  while (ros::ok()) {
    std_msgs::String msg;

    std::stringstream ss;
    ss << "hello world " << count;
    msg.data = ss.str();
    ROS_INFO("I say: [%s]", msg.data.c_str());
    chatter_pub.publish(msg);

    //
    robomaster_msg::Num num;
    num.value = count;
    chatter_num_pub.publish(num);
    num.value++;
    //
    ros::spinOnce();

    loop_rate.sleep();
    ++count;
  }

  return 0;
}