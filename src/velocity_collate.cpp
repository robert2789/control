#include <ros/ros.h>
#include <std_msgs/Float64.h>
#include <sensor_msgs/Range.h>
#include <geometry_msgs/Twist.h>







geometry_msgs::Twist output;
	
void callbackHeight(const geometry_msgs::Twist& msg){
	
	output.linear.z = msg.linear.z;
}
	

void callbackMoveBase(const geometry_msgs::Twist& msg){ 


	output.linear.x = msg.linear.x;
	output.linear.y = msg.linear.y;
	output.angular.x = msg.angular.x;
	output.angular.y = msg.angular.y;
	output.angular.z = msg.angular.z;
}

int main(int argc, char **argv){
	
	output.linear.x = 0.0;
	output.linear.y = 0.0;
	output.linear.z = 0.0;
	output.angular.x = 0.0;
	output.angular.y = 0.0;
	output.angular.z = 0.0;


	ros::init(argc, argv, "velocity_collator");
	
	ros::NodeHandle nodeHandle;
	ros::Subscriber subscriberHeight = nodeHandle.subscribe("quadrotor/vel_cmd_height", 1, callbackHeight);
	ros::Subscriber subscriberMoveBase = nodeHandle.subscribe("cmd_vel", 1, callbackMoveBase);
	ros::Publisher publisher = nodeHandle.advertise<geometry_msgs::Twist>("quadrotor/vel_cmd_collated", 1);
	

	ros::Rate naptime(100);
while(ros::ok()){
		publisher.publish(output);
		ros::spinOnce();
		naptime.sleep();
		}

return 0;
}
