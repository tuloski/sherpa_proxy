#ifndef _GETJSONVALUE_
#define _GETJSONVALUE_

#include "rosmsgs.h"
#include "std_msgs/String.h"
#include <jsoncpp/json/json.h>


Json::Value get_json_value(std_msgs::String msg);	
//Json::Value get_json_value(mhri_msgs::multimodal_action msg);
//Json::Value get_json_value(mhri_msgs::multimodal msg);
Json::Value get_json_value(camera_handler_sherpa::Camera msg);
Json::Value get_json_value(geometry_msgs::Twist msg);
Json::Value get_json_value(lrs_msgs_common::LeashingCommand msg);
Json::Value get_json_value(lrs_msgs_common::LeashingStatus msg);
#endif
