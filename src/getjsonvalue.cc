#include "getjsonvalue.h"

using namespace std;

/** Multimodal action -> Json */
/*Json::Value get_json_value(mhri_msgs::multimodal_action msg) {
  
  Json::Value res;
  res["selected"] = msg.selected;
  res["type"] = msg.type;
  res["command"] = msg.command;
  res["data"] = msg.data;
  res["direction"]["x"] = msg.direction[0];
  res["direction"]["y"] = msg.direction[1];
  res["direction"]["z"] = msg.direction[2];
  res["location"]["x"] = msg.location[0];
  res["location"]["y"] = msg.location[1];
  res["location"]["z"] = msg.location[2];
  res["confidence"] = msg.confidence;
  res["source"] = msg.source;

  return res;
}*/

/*Json::Value get_json_value(mhri_msgs::multimodal msg) {

  Json::Value res;
  int interp_size = msg.action.size();

  res["action_size"] = interp_size;
  for( unsigned int i=0; i < interp_size; i++ ) {
    res["value"][i] = msg.action[i].value.data;
    res["error"][i] = msg.action[i].error.data;
    res["type"][i] = msg.action[i].type.data;
    res["pose"][i]["x"] = msg.action[i].pose.position.x;
    res["pose"][i]["y"] = msg.action[i].pose.position.y;
    res["pose"][i]["z"] = msg.action[i].pose.position.z;
    res["pose"][i]["qw"] = msg.action[i].pose.orientation.w;
    res["pose"][i]["qx"] = msg.action[i].pose.orientation.x;
    res["pose"][i]["qy"] = msg.action[i].pose.orientation.y;
    res["pose"][i]["qz"] = msg.action[i].pose.orientation.z;
  }

  return res;

}*/

Json::Value get_json_value(camera_handler_sherpa::Camera msg) {

  Json::Value res;
  res["taken_photo"] = msg.taken_photo;
  res["taken_video"] = msg.taken_video;
  res["N_photo_taken"] = msg.N_photo_taken;
  res["N_video_taken"] = msg.N_video_taken;
  res["path_photo"] = msg.path_photo;
  res["path_video"] = msg.path_video;
  res["geopose"]["latitude"] = msg.geopose.position.latitude;
  res["geopose"]["longitude"] = msg.geopose.position.longitude;
  res["geopose"]["altitude"] = msg.geopose.position.altitude;
  res["geopose"]["qw"] = msg.geopose.orientation.w;
  res["geopose"]["qx"] = msg.geopose.orientation.x;
  res["geopose"]["qy"] = msg.geopose.orientation.y;
  res["geopose"]["qz"] = msg.geopose.orientation.z;

  return res;
}

Json::Value get_json_value(geometry_msgs::Twist msg) {

  Json::Value res;
  res["linear"]["x"] = msg.linear.x;
  res["linear"]["y"] = msg.linear.y;
  res["linear"]["z"] = msg.linear.z;
  res["angular"]["x"] = msg.angular.x;
  res["angular"]["y"] = msg.angular.y;
  res["angular"]["z"] = msg.angular.z;

  return res;
}

Json::Value get_json_value(lrs_msgs_common::LeashingCommand msg) {

  Json::Value res;
  res["horizontal_distance"] = msg.horizontal_distance;
  res["horizontal_distance_vel"] = msg.horizontal_distance_vel;
  res["horizontal_heading"] = msg.horizontal_heading;
  res["horizontal_heading_vel"] = msg.horizontal_heading_vel;
  res["distance_north"] = msg.distance_north;
  res["distance_north_vel"] = msg.distance_north_vel;
  res["distance_east"] = msg.distance_east;
  res["distance_east_vel"] = msg.distance_east_vel;
  res["horizontal_control_mode"] = msg.horizontal_control_mode;
  res["vertical_distance"] = msg.vertical_distance;
  res["vertical_distance_vel"] = msg.vertical_distance_vel;
  res["vertical_control_mode"] = msg.vertical_control_mode;
  res["yaw"] = msg.yaw;
  res["yaw_vel"] = msg.yaw_vel;
  res["yaw_control_mode"] = msg.yaw_control_mode;
  res["yawpoint"]["latitude"] = msg.yawpoint.latitude;
  res["yawpoint"]["longitude"] = msg.yawpoint.longitude;
  res["yawpoint"]["altitude"] = msg.yawpoint.altitude;

  return res;
}

Json::Value get_json_value(lrs_msgs_common::LeashingStatus msg) {

  Json::Value res;
  res["horizontal_distance"] = msg.horizontal_distance;
  res["horizontal_heading"] = msg.horizontal_heading;
  res["distance_north"] = msg.distance_north;
  res["distance_east"] = msg.distance_east;
  res["horizontal_control_mode"] = msg.horizontal_control_mode;
  res["vertical_distance"] = msg.vertical_distance;
  res["vertical_control_mode"] = msg.vertical_control_mode;
  res["yaw"] = msg.yaw;
  res["yaw_control_mode"] = msg.yaw_control_mode;
  res["yawpoint"]["latitude"] = msg.yawpoint.latitude;
  res["yawpoint"]["longitude"] = msg.yawpoint.longitude;
  res["yawpoint"]["altitude"] = msg.yawpoint.altitude;

  return res;
}

Json::Value get_json_value(std_msgs::String msg) {
  Json::Value res;
  res["data"] = msg.data;
  return res;
}

