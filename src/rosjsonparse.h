#ifndef _ROSJSONPARSE_
#define _ROSJSONPARSE_

#include "rosmsgs.h"
#include <jsoncpp/json/json.h>

bool ros_json_parse( Json::Value m, std_msgs::String & str );
bool ros_json_parse( Json::Value m, mhri_msgs::multimodal_action & action );
bool ros_json_parse( Json::Value m, mhri_msgs::multimodal & interp );

#endif
