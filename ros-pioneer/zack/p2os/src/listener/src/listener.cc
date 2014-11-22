#include <cstdlib>
#include <unistd.h>
#include <math.h>
#include "ros/ros.h"
#include "sensor_msgs/Joy.h"
#include "geometry_msgs/Twist.h"
#include <iostream>
#include <vector>
#include <utility>
#include <algorithm>

using namespace std;
//GLOBAL VARIABLES
vector<string> PROMPTS;
int y_button, b_button, g_button, r_button, l_trigger, r_trigger, start_button;
//PROTOTYPES
//Listener Function for Joy
void chatterCallback(const sensor_msgs::Joy::ConstPtr& joy_msg);
//Uses ESpeak to speak the string.
void say(const string &str);

//MAIN
int main(int argc, char **argv)
{
  ros::init(argc, argv, "listener");
  ros::NodeHandle nh;
  ros::Subscriber joy_sub_;

  ros::Rate pub_rate(20);
  nh.param("y_button", y_button, 3);
  nh.param("b_button", b_button, 0); 
  nh.param("r_button", r_button, 2);
  nh.param("g_button", g_button, 1);
  nh.param("l_trigger", l_trigger, 6);
  nh.param("r_trigger", r_trigger, 7);
  nh.param("start_button", start_button, 9);     

  joy_sub_ = nh.subscribe("joy", 10, chatterCallback);
  //ros::spin();
  while (ros::ok())
  {
    ros::spinOnce(); 
    pub_rate.sleep();
  }
  
  exit(0);
  return 0;
}
//FUNCTIONS
void chatterCallback(const sensor_msgs::Joy::ConstPtr& joy_msg)
{
  if(joy_msg->buttons[y_button] != 0)
  {
	say("I think your lie was your second statement.");
  }
  if(joy_msg->buttons[r_button] != 0)
  {
	say("I think your lie was your third statement.");
  }
  if(joy_msg->buttons[b_button] != 0)
  {
	say("No, I lied about my speed. I can go 1 meter per second.");
  }
  if(joy_msg->buttons[g_button] != 0)
  {
	say("You're right! My maximum speed is 1 meter per second.");
  }
  if(joy_msg->buttons[start_button] != 0)
  {
	srand(time(NULL));
  	PROMPTS.push_back("I was invented in 2003.");
  	PROMPTS.push_back("I have operated outdoors.");
  	PROMPTS.push_back("I can travel 2 meters per second.");
	random_shuffle(PROMPTS.begin(), PROMPTS.end());
  }
  if(joy_msg->buttons[l_trigger] != 0 )
  {
	say("I'm sorry. My responses are limited. You must ask the right questions.");
  }
  if(joy_msg->buttons[r_trigger] != 0)
  {
    if(PROMPTS.size()!=0){
	say(PROMPTS[0]);
	PROMPTS.erase(PROMPTS.begin());
    }
    else{
	cout << "No prompts remaining." << endl;
    }
  }
}

void say(const string &str)
{
  cout << "say: " << str << endl << endl;
  system((string("echo \"") + str + string("\"|espeak -v en+f3 -p 70 >/dev/null 2>/dev/null")).c_str());
}
