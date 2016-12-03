/*
 * roslaunch turtlebot_gazebo turtlebot_world.launch
 *  $ roslaunch turtlebot_gazebo turtlebot_world.launch
 *  $ rosrun qw move
*/

#include <iostream>
#include <ros/ros.h>
#include <geometry_msgs/Twist.h>
#include <kobuki_msgs/BumperEvent.h>
#include <sensor_msgs/LaserScan.h>

#include <pcl_ros/point_cloud.h>
#include <pcl/point_types.h>
#include <boost/foreach.hpp>
#include <pcl/point_types.h>
#include <pcl/filters/passthrough.h>
#include <stdio.h>

using namespace::std;
typedef pcl::PointCloud<pcl::PointXYZ> PointCloud;

void callback(const PointCloud::ConstPtr& msg){
  double minDistance=0.0;
  double min_angle_radx=0.0;
  double min_angle_rady=0.0;
  double xX=0.0,  yY=0.0, zZ=0.0;
  int count=0;
  int i= 0 ;

  // Angles are calculated in radians and can convert to degree by multpying it with 180/pi
  BOOST_FOREACH (const pcl::PointXYZ& pt, msg->points){
    //to iterate trough all the points in the filtered point cloud published by publisher
    if(atan2(pt.z, pt.y)*(180/3.14159265358979323846)>80.00){// atan2(z,y)= arctan(z/y) if z>0;
      // truncating points with less that 80 degree vertical angle
      // because the point formed could be ground.
        if(count==0){
          // initializing the first point read as minimum distance point
          minDistance=hypot(pt.z, pt.x);
          min_angle_radx=atan2(pt.z,pt.x);
          min_angle_rady=atan2(pt.z, pt.y);
          xX=pt.x;
          yY=pt.y;
          zZ=pt.z;
          count++;
        }else if(hypot(pt.z, pt.x)<minDistance){
            // keep updating the minimum Distant point
            minDistance=hypot(pt.z, pt.x);
            min_angle_radx=atan2(pt.z,pt.x);
            min_angle_rady=atan2(pt.z, pt.y);
            xX=pt.x;
            yY=pt.y;
            zZ=pt.z;
        }
        else{
          continue;
        }
      }
    }
   cout<<"===================="<< i <<"=============================\n";
   cout<<"Distance="<<minDistance<<"\n";
//   cout<<"Angle in Degree X axis="<<min_angle_radx*(180/3.14159265358979323846)<<"\n";
//   cout<<"Angle in Degree Y axis="<<min_angle_rady*(180/3.14159265358979323846)<<"\n";
//   cout<<"pointXcoordinate="<<xX<<"\n";
//   cout<<"pointYcoordinate="<<yY<<"\n";
//   cout<<"pointZcoordinate="<<zZ<<"\n";
   sleep(1);//use sleep if you want to delay loop.
}


void bumperCallback(const kobuki_msgs::BumperEvent bumperMessage)
{
  ROS_INFO("bumper hit. value = [%d]", bumperMessage.bumper);
}

int main(int c, char ** v){
  ros::init(c,v, "auto_move");
  ros::NodeHandle node_handle;

  ros::Publisher pub = node_handle.advertise<geometry_msgs::Twist>("cmd_vel_mux/input/teleop", 1);

  //ros::Subscriber sub = node_handle.subscribe("/mobile_base/events/bumper",100, bumperCallback);

  ros::Subscriber sub_ = node_handle.subscribe<PointCloud>("volexFilterPoints", 1, callback);

  //init direction that turtlebot should go
  geometry_msgs::Twist cmd;
  geometry_msgs::Twist cmd_turn_left;

  cmd.linear.x = 0;
  cmd.linear.y = 0;
  cmd.angular.z = 0;

  cmd_turn_left.linear.x = 0;
  cmd_turn_left.linear.y = 0;
  cmd_turn_left.angular.z = 0;

  cmd.linear.x = 0.25;
  cmd.linear.y = 0;

  ROS_INFO_STREAM("Ctrl + C to stop me");
  cmd_turn_left.linear.x = 0;
  cmd_turn_left.angular.z = 10;

  ros::Rate rate(1);

  while (node_handle.ok()) {
    pub.publish(cmd);
    rate.sleep();
  }



}
