#include <ros/ros.h>
#include <std_msgs/Float64.h>
#include <sensor_msgs/Range.h>
#include <geometry_msgs/Twist.h>



std_msgs::Float64 current;
std_msgs::Float64 desired; 
	
void callback(const sensor_msgs::Range& msg){
	if((msg.range > msg.min_range) && (msg.range < msg.max_range)){
		current.data = msg.range;
		
		}
	else{ROS_INFO("height out of range! Current height = '%f'", msg.range);
			current.data = 100.0;}

}		
	

int main(int argc, char **argv){
	
	
	
	ros::init(argc, argv, "height_control");
	
	ros::NodeHandle nodeHandle;
	ros::Subscriber subscriber = nodeHandle.subscribe("sensor/sonar", 1, callback);
	ros::Publisher publisher = nodeHandle.advertise<geometry_msgs::Twist>("quadrotor/vel_cmd_height", 1);
	

	
	ros::Rate naptime(100);
	
	double gain = 1.0;
	double error = 0.0;
	current.data = 0.0;
	desired.data = 1.5;
	
	geometry_msgs::Twist output;
	output.linear.x = 0.0;
	output.linear.y = 0.0;
	output.linear.z = 0.0;
	output.angular.x = 0.0;
	output.angular.y = 0.0;
	output.angular.z = 0.0;
	
	
	

	while(ros::ok()){
		if(current.data == 100){
				output.linear.z = 0.0;
				publisher.publish(output);
		}else{	
		error = desired.data - current.data;
		output.linear.z = error*gain;
		publisher.publish(output);
		}
		ros::spinOnce();
		naptime.sleep();
		}

return 0;

}

