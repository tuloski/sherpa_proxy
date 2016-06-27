#ifndef _CALLBACKS_H
#define _CALLBACKS_H

#include "rosmsgs.h"
#include "ros/message_event.h"

#include "ros/ros.h"
#include "getjsonvalue.h"
#include "roszyre.h"
#include "std_msgs/String.h"

void test_string_callback (const ros::MessageEvent<std_msgs::String const>& event);
void camera_callback (const ros::MessageEvent<camera_handler_sherpa::Camera const>& event);
void operator_control_velocity_callback (const ros::MessageEvent<geometry_msgs::Twist const>& event);
void leashing_command_callback (const ros::MessageEvent<lrs_msgs_common::LeashingCommand const>& event);
void leashing_status_callback (const ros::MessageEvent<lrs_msgs_common::LeashingStatus const>& event);
//void multimodal_cmd_cb ( const ros::MessageEvent<mhri_msgs::multimodal_action const>& event);
//void interpretation_cb ( const ros::MessageEvent<mhri_msgs::multimodal const>& event);

#endif

