cmake_minimum_required(VERSION 2.8.3)
project(dem_wall_following)

## Find catkin macros and libraries
## if COMPONENTS list like find_package(catkin REQUIRED COMPONENTS xyz)
## is used, also find other catkin packages
find_package(catkin REQUIRED COMPONENTS
  roscpp
  rospy
  std_msgs
  genmsg
)

find_package(PCL 1.7 REQUIRED)
find_package(catkin REQUIRED COMPONENTS tf)

catkin_package(
#  INCLUDE_DIRS include
#  LIBRARIES dem_wall_following
#  CATKIN_DEPENDS roscpp rospy std_msgs
#  DEPENDS system_lib
)


include_directories(include ${catkin_INCLUDE_DIRS} ${PCL_INCLUDE_DIRS} )
link_directories(${PCL_LIBRARY_DIRS})
add_definitions(${PCL_DEFINITIONS} ${PCL_DEFINITIONS})


set (SRCS1 ${SRCS1} src/node_wallFollowing.cpp)
set (SRCS1 ${SRCS1} src/wallFollowing.cpp)
include_directories(include ${catkin_INCLUDE_DIRS})

add_executable(wallFollowing ${SRCS1})
target_link_libraries(wallFollowing ${catkin_LIBRARIES})

#move.cpp
add_executable(move src/move.cpp)
target_link_libraries(move ${catkin_LIBRARIES})


add_executable(talker src/talker.cpp)
target_link_libraries(talker ${catkin_LIBRARIES})


add_executable(listener src/listener.cpp)
target_link_libraries(listener ${catkin_LIBRARIES})


# Distance
add_executable(pub_kfc src/pub.cpp)
target_link_libraries(pub_kfc ${catkin_LIBRARIES} ${OpenCV_LIBRARIES} ${PCL_LIBRARIES} )
add_dependencies(pub_kfc test_generate_messages_cpp)


add_executable(sub_kfc src/sub.cpp)
target_link_libraries(sub_kfc ${catkin_LIBRARIES} ${OpenCV_LIBRARIES} ${PCL_LIBRARIES} )
add_dependencies(sub_kfc test_generate_messages_cpp)
