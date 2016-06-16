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

Json::Value get_json_value(std_msgs::String msg) {
  Json::Value res;
  res["data"] = msg.data;
  return res;
}

