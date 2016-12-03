#include "ros/ros.h"
#include "sensor_msgs/LaserScan.h"
#include "geometry_msgs/Twist.h"
#include <iostream>
using namespace std;
ros::Publisher cmd_vel;
int z = 0;
void scanCallback(const sensor_msgs::LaserScan::ConstPtr& scan_msg)
{
    //cout << z; z++;
    /** this is to verify whether i am able to obtain the data i need*/
    cout<<scan_msg->header.seq;

//    ROS_INFO("I see: %u", scan_msg->header.seq);
//    ROS_INFO("I see: %f", scan_msg->angle_min);
//    ROS_INFO("I see: %f", scan_msg->time_increment);
//    for (int y=150; y<=155; y++)
//    {
////      ROS_INFO("I see: %f", scan_msg->ranges[y]);
//    }

//    for (int y=150; y<=1406; y++)
//    {
//        geometry_msgs::Twist move_cmd;
//        move_cmd.angular.z = 0.2;
//        move_cmd.linear.x = 0.5;
//        cmd_vel.publish(move_cmd);
//    }

}

int main(int argc, char **argv)
{

    cout<<"hello quy ";
    ros::init(argc, argv, "wall_listener");
    ros::NodeHandle n;

    ros::Subscriber sub = n.subscribe("/scan", 1000, scanCallback);

    cmd_vel = n.advertise<geometry_msgs::Twist>("/cmd_vel", 1000);

    ros::spin();

    return 0;
}
