#ifndef _CALLBACKS_H
#define _CALLBACKS_H

#include "rosmsgs.h"
#include "ros/message_event.h"

#include "ros/ros.h"
#include "getjsonvalue.h"
#include "roszyre.h"
#include "std_msgs/String.h"

void test_string_callback (const ros::MessageEvent<std_msgs::String const>& event);
void multimodal_cmd_cb ( const ros::MessageEvent<mhri_msgs::multimodal_action const>& event);
void interpretation_cb ( const ros::MessageEvent<mhri_msgs::multimodal const>& event);

#endif

