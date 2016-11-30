#include "node_wallFollowing.h"

#define SUBSCRIBER_BUFFER_SIZE 1  // Size of buffer for subscriber.
#define PUBLISHER_BUFFER_SIZE 1000  // Size of buffer for publisher.

//#define WALL_DISTANCE 0.13
//#define MAX_SPEED 0.1
//#define P 10    // Proportional constant for controller
//#define D 5     // Derivative constant for controller
//#define ANGLE_COEF 1    // Proportional constant for angle controller
//#define DIRECTION 1 // 1 for wall on the left side of the robot (-1 for the right side).
// #define PUBLISHER_TOPIC "/syros/base_cmd_vel"
//#define PUBLISHER_TOPIC "/cmd_vel"
// #define SUBSCRIBER_TOPIC "/syros/laser_laser"
//#define SUBSCRIBER_TOPIC "/base_scan"

int main(int argc, char **argv)
{
  //Initialization of node
  ros::init(argc, argv, "wallFollowing");
  ros::NodeHandle n;

  //Creating publisher
  ros::Publisher pubMessage = n.advertise<geometry_msgs::Twist>("/cmd_vel", PUBLISHER_BUFFER_SIZE);

  //Creating object, which stores data from sensors and has methods for
  //publishing and subscribing
  //NodeWallFollowing *nodeWallFollowing = new NodeWallFollowing(pubMessage, WALL_DISTANCE, MAX_SPEED, DIRECTION, P, D, 1);

  //variables
    double wallDistance = 0.13; // Desired distance from the wall.
    double e = 0;            // Difference between desired distance from the wall and actual distance.
    double diffE = 0;     // Derivative element for PD controller;
    double maxSpeed = 0.1;     // Maximum speed of robot.
    double P = 10;            // k_P Constant for PD controller.
    double D = 5;            // k_D Constant for PD controller.
    double angleCoef = 1;    // Coefficient for P controller.
    int direction = 1;      // 1 for wall on the right side of the robot (-1 for the left one).
    double angleMin = 0;     // Angle, at which was measured the shortest distance.
    double distFront = 0;    // Distance, measured by ranger in front of robot.

   NodeWallFollowing *nodeWallFollowing = new NodeWallFollowing(//variables
                                                                wallDistance, // Desired distance from the wall.
                                                                e,            // Difference between desired distance from the wall and actual distance.
                                                                diffE,        // Derivative element for PD controller;
                                                                maxSpeed,     // Maximum speed of robot.
                                                                P,            // k_P Constant for PD controller.
                                                                D,            // k_D Constant for PD controller.
                                                                angleCoef,    // Coefficient for P controller.
                                                                direction,      // 1 for wall on the right side of the robot (-1 for the left one).
                                                                angleMin,     // Angle, at which was measured the shortest distance.
                                                                distFront,    // Distance, measured by ranger in front of robot.
                                                                pubMessage);

  //Creating subscriber and publisher
  ros::Subscriber sub = n.subscribe("/syros/laser_laser", SUBSCRIBER_BUFFER_SIZE, &NodeWallFollowing::messageCallback, nodeWallFollowing);
  //ros::spin();

  return 1;
}
