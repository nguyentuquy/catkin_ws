#include <ros/ros.h>
#include <sensor_msgs/PointCloud2.h>
#include <pcl_conversions/pcl_conversions.h>
#include <pcl/point_cloud.h>
#include <pcl/point_types.h>
#include <pcl/filters/voxel_grid.h>
#include <pcl/filters/crop_box.h>
#include <ros/ros.h>

#include <pcl_ros/point_cloud.h>
#include <pcl/point_types.h>
#include <boost/foreach.hpp>
#include <pcl/point_types.h>
#include <pcl/filters/passthrough.h>
#include <stdio.h>

using namespace::std;
ros::Publisher pub;
/* you can find explanation to this code in 
*http://wiki.ros.org/pcl/Tutorials
*The catch is, in the tutorial they are subscribing to camera/depth/points but you are suppose to 
*subscribe to /camera/depth_registered/points
*Don't forget to launch openni.launch before running this code.
*/
void cloud_cb (const sensor_msgs::PointCloud2ConstPtr& input){
  sensor_msgs::PointCloud2 output;
  pcl::PCLPointCloud2* cloud =new pcl::PCLPointCloud2;
  pcl::PCLPointCloud2ConstPtr cloudPtr(cloud);
  pcl::PCLPointCloud2 cloud_filtered;
  pcl_conversions::toPCL(*input, *cloud);
  pcl::VoxelGrid<pcl::PCLPointCloud2> sor;
  sor.setInputCloud (cloudPtr);
  sor.setLeafSize(0.01,0.01,0.01);
  sor.filter (cloud_filtered);
  pcl_conversions::fromPCL(cloud_filtered, output);
  pub.publish (output);
}
/***/

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
   cout<<"==========pub=========="<< i <<"=============================\n";
   cout<<"Distance="<<minDistance<<"\n";
//   cout<<"Angle in Degree X axis="<<min_angle_radx*(180/3.14159265358979323846)<<"\n";
//   cout<<"Angle in Degree Y axis="<<min_angle_rady*(180/3.14159265358979323846)<<"\n";
//   cout<<"pointXcoordinate="<<xX<<"\n";
//   cout<<"pointYcoordinate="<<yY<<"\n";
//   cout<<"pointZcoordinate="<<zZ<<"\n";
   sleep(2);//use sleep if you want to delay loop.
}

int main (int argc, char** argv){
  ros::init (argc, argv,"pub_kfc");
  ros::NodeHandle nh;
  ros::Subscriber sub = nh.subscribe ("/camera/depth_registered/points", 1,cloud_cb);
  pub = nh.advertise<sensor_msgs::PointCloud2> ("volexFilterPoints", 1);

  ros::Subscriber sub2 = nh.subscribe<PointCloud>("volexFilterPoints", 1, callback);

  ros::spin ();
  return 0;
}
