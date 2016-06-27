#ifndef _ROSJSONPARSE_
#define _ROSJSONPARSE_

#include "rosmsgs.h"
#include <jsoncpp/json/json.h>

bool ros_json_parse( Json::Value m, std_msgs::String & str );
//bool ros_json_parse( Json::Value m, mhri_msgs::multimodal_action & action );
//bool ros_json_parse( Json::Value m, mhri_msgs::multimodal & interp );
bool ros_json_parse( Json::Value res, camera_handler_sherpa::Camera & camera );
bool ros_json_parse( Json::Value res, geometry_msgs::Twist & twist );
bool ros_json_parse( Json::Value res, lrs_msgs_common::LeashingCommand & leashing_command );
bool ros_json_parse( Json::Value res, lrs_msgs_common::LeashingStatus & leashing_status );

#endif
