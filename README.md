
1. Move Robot : 

rostopic pub -1 /turtle1/cmd_vel geometry_msgs/Twist -- '[2.0, 0.0, 0.0]' '[0.0, 0.0, 1.8]'

2. See movement of Robot with Graphic: 5 . Using rqt_plot

	rosrun rqt_plot rqt_plot

3. Set permission for file/folder

	sudo chmod -R 777 ~/catkin_ws/devel/setup.bash

4. Bevor lauch Talker oder Listener muss man diesen Command schreiben.

	source devel/setup.bash

5. How to run tutorial 11:

	5.1 Start with command: 
		roscore
	5.2 Run Talker and Listener

		source devel/setup.bash
		rosrun beginner_tutorials talker
and
		source devel/setup.bash
		rosrun beginner_tutorials listener				
6. Load Terminal-Tabs:
	gnome-terminal --load-config=/tmp/cfg

7. Pass
93916646

8. Move Emulator with C++
	8.1 Gazebo Starten :
		roslaunch turtlebot_gazebo turtlebot_world.launch world_file:=/opt/ros/indigo/share/turtlebot_gazebo/worlds/empty.world

	8.2 C++ Compile
		$ cd ~/catkin_ws	
		$ Catkin_make
	8.3 roslaunch
		$ roslaunch turtlebot_gazebo amcl_demo.launch 
	8.4 Run Robot (Navigation)
		$ rosrun simple_navigation_goals simple_navigation_goals
9. Parse a urdf file
	http://wiki.ros.org/urdf/Tutorials/Parse%20a%20urdf%20file
	with some right url with something like : /home/opt/.../parser /home/opt/...urdf/my_robot.urdf

10. nav2d installation
	roslaunch nav2d_tutorials tutorial1.launch

11. ResourceNotFound: p2os_urdf
	p2os_urdf is optional, because it's not released into indigo. You can either get the source code from github, or just uncomment the part from the launch file. (It's only used to show the pioneer-model in RVIZ)

12. chmod :
	sudo chmod -R 777 /home/sixven/camp_sms/inputs

13. Keyboard Controll Robot
	13.1 gazebo Starten
roslaunch turtlebot_gazebo turtlebot_world.launch world_file:=/opt/ros/indigo/share/turtlebot_gazebo/worlds/empty.world

	13.2 keyboard setup
	roslaunch turtlebot_teleop keyboard_teleop.launch

14. Testing the New Map : http://learn.turtlebot.com/2015/02/03/8/
	14.1 gazebo starten
		$ roslaunch turtlebot_gazebo turtlebot_world.launch
	14.2 start map building
		$ roslaunch turtlebot_gazebo gmapping_demo.launch
	14.3 Rviz launch
		$ roslaunch turtlebot_rviz_launchers view_navigation.launch
	14.4 teleop launch
		$ roslaunch turtlebot_teleop keyboard_teleop.launch

15. Robot move auto with programm
	15.1 start gazebo
		$ roslaunch turtlebot_gazebo turtlebot_world.launch
	15.2 code running
		$ python move_robot.py
16. OpenCV
	16.1 run code C++/C opencv 
		$ g++ -o file_to_run code_to_run.cpp `pkg-config opencv --cflags --libs`
		$ g++ -o webcame_showing webcame_showing.cpp `pkg-config opencv --cflags --libs` 
	=>	$ ./file_to_run
	16.2 run code in Python
		$ python code_to_run.py
17. Hector SLAM
	17.1 run command:
		$ roslaunch hector_slam_launch tutorial.launch
	17.2 scan Map with .bag
		$ rosbag play Team_Hector_MappingBox_RoboCup_2011_Rescue_Arena.bag  --clock

18. find package
	$ rospack find turtlesim

19.Run turtlebot & hector
	 $ roslaunch turtlebot_hector_mapping hector_turtlebot_willowgarage.launch
 
20. Autonomous Navigation(2D NAV goal)
	http://learn.turtlebot.com/2015/02/03/9/

21.SSh
	$ ssh turtlebot@192.168.0.108

22. Slam with Gmapping
	21.1 Bringup robot
		$  roslaunch turtlebot_bringup minimal.launch
	21.2 Gmapping launch
		$  roslaunch turtlebot_navication gmapping_demo.launch
	21.3 Teleop_keyboard
		$  roslaunch turtlebot_teleop keyboard_teleop.launch 

22. Distance to Wall
	22.1 launch Gazebo
	$  roslaunch turtlebot_gazebo turtlebot_world.launch

	22.2 Lau openni
	$  roslaunch openni_launch openni.launch
	
	22.3 Run Pub
	$  rosrun dem_wall_following pub_kfc

	22.4 Run sub
	$ rosrun dem_wall_following sub_kfc

	22.5 run RVIZ
	$ roslaunch turtlebot_rviz_launchers view_robot.launch
23. Do khoang cach giua tuong voi robot
	23.1 launch Gazebo
	$  roslaunch turtlebot_gazebo turtlebot_world.launch

	23.2 Lau openni
	$  roslaunch openni_launch openni.launch
	
	23.3 Run Pub(tu pub & tu sub)
	$  rosrun dem_wall_following pub_kfc





