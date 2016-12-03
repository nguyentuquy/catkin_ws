#include "node_wallFollowing.h"
#include <iostream>
#include "std_msgs/String.h"
#include <sstream>
using namespace std;

#define WALL_DISTANCE 0.13
#define MAX_SPEED 0.1
#define P 10    // Proportional constant for controller
#define D 5     // Derivative constant for controller
#define ANGLE_COEF 1    // Proportional constant for angle controller
#define DIRECTION 1 // 1 for wall on the left side of the robot (-1 for the right side).
// #define PUBLISHER_TOPIC "/syros/base_cmd_vel"

void chatterCallback(const sensor_msgs::LaserScan::ConstPtr& msg)
{
  int size = msg->ranges.size();

  ROS_INFO("size : %d", size);

//  //Variables whith index of highest and lowest value in array.
//  int minIndex = size*(direction+1)/4;
//  int maxIndex = size*(direction+3)/4;

//  //This cycle goes through array and finds minimum
//  for(int i = minIndex; i < maxIndex; i++)
//  {
//    if (msg->ranges[i] < msg->ranges[i] && msg->ranges[i] > 0.0){
//      minIndex = i;
//    }
//  }

//  //Calculation of angles from indexes and storing data to class variables.
//  angleMin = (minIndex-size/2)*msg->angle_increment;
//  double distMin;
//  distMin = msg->ranges[minIndex];
//  distFront = msg->ranges[size/2];
//  diffE = (distMin - wallDistance) - PI;
//  e = distMin - wallDistance;

//  //Invoking method for publishing message
//  publishMessage();
}


int main(int argc, char **argv)
{
  //Initialization of node
  ros::init(argc, argv, "wallFollowing");
  ros::NodeHandle n;

  //Creating publisher
  ros::Publisher pubMessage = n.advertise<geometry_msgs::Twist>("/cmd_vel", 1000);

  //Creating subscriber and publisher
  ros::Subscriber sub = n.subscribe("/base_scan", 1000, chatterCallback);

  ros::Rate loop_rate(10);

  int count =0;
  while (ros::ok())
    {
//      //preparing message
//      geometry_msgs::Twist msg;

//      msg.angular.z = 0.5 ;//direction*(P*e + D*diffE) + angleCoef * (angleMin - PI*direction/2);    //PD controller

//      if (distFront < 1.0){
//        msg.linear.x = 0;
//      }
//      else if (distFront < 1.0 * 2){
//        msg.linear.x = 0.5*maxSpeed;
//      }
//      else if (fabs(angleMin)>1.75){
//        msg.linear.x = 0.4*maxSpeed;
//      }
//      else {
//        msg.linear.x = maxSpeed;
//      }

//      //publishing message
//      pubMessage.publish(msg);
    }

  ros::spin();
  return 0;
}
