#include "node_wallFollowing.h"
#include <math.h>
#include "ros/ros.h"
#include "sensor_msgs/LaserScan.h"
#define PI 3.141592


NodeWallFollowing::NodeWallFollowing(
                                      double wallDistance, // Desired distance from the wall.
                                      double e,            // Difference between desired distance from the wall and actual distance.
                                      double diffE,     // Derivative element for PD controller;
                                      double maxSpeed,     // Maximum speed of robot.
                                      double P,            // k_P Constant for PD controller.
                                      double D,            // k_D Constant for PD controller.
                                      double angleCoef,    // Coefficient for P controller.
                                      int direction,      // 1 for wall on the right side of the robot (-1 for the left one).
                                      double angleMin,     // Angle, at which was measured the shortest distance.
                                      double distFront,    // Distance, measured by ranger in front of robot.
                                      ros::Publisher pubMessage)
{
  this->wallDistance = wallDistance;
  this->e = e;
  this->diffE = diffE;
  this->P = p;
  this->D;
  this->angleCoef= angleCoef;
  this->direction = direction;
  this->angleMin = angleMin;
  this->distFront = distFront;
  this->pubMessage = pubMessage;
}

NodeWallFollowing::~NodeWallFollowing()
{
}

//Publisher
void NodeWallFollowing::publishMessage()
{
  //preparing message
  geometry_msgs::Twist msg;

  msg.angular.z = direction*(P*e + D*diffE) + angleCoef * (angleMin - PI*direction/2);    //PD controller

  if (distFront < wallDistance){
    msg.linear.x = 0;
  }
  else if (distFront < wallDistance * 2){
    msg.linear.x = 0.5*maxSpeed;
  }
  else if (fabs(angleMin)>1.75){
    msg.linear.x = 0.4*maxSpeed;
  }
  else {
    msg.linear.x = maxSpeed;
  }

  //publishing message
  pubMessage.publish(msg);
}

//Subscriber
void NodeWallFollowing::messageCallback(const sensor_msgs::LaserScan::ConstPtr& msg)
{
  int size = msg->ranges.size();

  //Variables whith index of highest and lowest value in array.
  int minIndex = size*(direction+1)/4;
  int maxIndex = size*(direction+3)/4;

  //This cycle goes through array and finds minimum
  for(int i = minIndex; i < maxIndex; i++)
  {
    if (msg->ranges[i] < msg->ranges[minIndex] && msg->ranges[i] > 0.0){
      minIndex = i;
    }
  }

  //Calculation of angles from indexes and storing data to class variables.
  angleMin = (minIndex-size/2)*msg->angle_increment;
  double distMin;
  distMin = msg->ranges[minIndex];
  distFront = msg->ranges[size/2];
  diffE = (distMin - wallDistance) - PI;
  e = distMin - wallDistance;

  //Invoking method for publishing message
  publishMessage();
}
