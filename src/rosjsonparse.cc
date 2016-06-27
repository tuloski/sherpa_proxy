#include "rosjsonparse.h"
#include "std_msgs/String.h"


using namespace std;

/*bool ros_json_parse( Json::Value m, mhri_msgs::multimodal_action & action ) {

  action.selected = m["selected"].asString();
  action.type = m["type"].asString();
  action.command = m["command"].asString();
  action.data = m["data"].asDouble();
  action.direction[0] = m["direction"]["x"].asDouble();
  action.direction[1] = m["direction"]["y"].asDouble();
  action.direction[2] = m["direction"]["z"].asDouble();
  action.location[0] = m["location"]["x"].asDouble();
  action.location[1] = m["location"]["y"].asDouble();
  action.location[2] = m["location"]["z"].asDouble();
  action.confidence = m["confidence"].asDouble();
  action.source = m["source"].asString();

  return true;
}*/

/*bool ros_json_parse( Json::Value m, mhri_msgs::multimodal & cmds ) {

  int s = m["action_size"].asInt();

  for( int i=0; i<s;i++ ) {
    
    mhri_msgs::interpretation interp;

    interp.value.data = m["value"][i].asInt();
    interp.error.data = m["error"][i].asString();
    interp.type.data = m["type"][i].asString();
    interp.pose.position.x = m["pose"][i]["x"].asDouble();
    interp.pose.position.y = m["pose"][i]["y"].asDouble();
    interp.pose.position.z = m["pose"][i]["z"].asDouble();
    interp.pose.orientation.w = m["pose"][i]["qw"].asDouble();
    interp.pose.orientation.x = m["pose"][i]["qx"].asDouble();
    interp.pose.orientation.y = m["pose"][i]["qy"].asDouble();
    interp.pose.orientation.z = m["pose"][i]["qz"].asDouble();

    cmds.action.push_back( interp );
  }

  return true; 

}*/

bool ros_json_parse( Json::Value res, camera_handler_sherpa::Camera & camera ) {

	camera.taken_photo = res["taken_photo"].asBool();
	camera.taken_video = res["taken_video"].asBool();
	camera.N_photo_taken = res["N_photo_taken"].asInt();
	camera.N_video_taken = res["N_video_taken"].asInt();
	camera.path_photo = res["path_photo"].asString();
	camera.path_video = res["path_video"].asString();
	camera.geopose.position.latitude = res["geopose"]["latitude"].asDouble();
	camera.geopose.position.longitude = res["geopose"]["longitude"].asDouble();
	camera.geopose.position.altitude = res["geopose"]["altitude"].asDouble();
	camera.geopose.orientation.w = res["geopose"]["qw"].asDouble();
	camera.geopose.orientation.x = res["geopose"]["qx"].asDouble();
	camera.geopose.orientation.y = res["geopose"]["qy"].asDouble();
	camera.geopose.orientation.z = res["geopose"]["qz"].asDouble();

	return true;

}

bool ros_json_parse( Json::Value res, geometry_msgs::Twist & twist ) {

	twist.linear.x = res["linear"]["x"].asDouble();
	twist.linear.y = res["linear"]["y"].asDouble();
	twist.linear.z = res["linear"]["z"].asDouble();
	twist.angular.x = res["angular"]["x"].asDouble();
	twist.angular.y = res["angular"]["y"].asDouble();
	twist.angular.z = res["angular"]["z"].asDouble();

	return true;

}

bool ros_json_parse( Json::Value res, lrs_msgs_common::LeashingCommand & leashing_command ) {

	leashing_command.horizontal_distance = res["horizontal_distance"].asDouble();
	leashing_command.horizontal_distance_vel = res["horizontal_distance_vel"].asDouble();
	leashing_command.horizontal_heading = res["horizontal_heading"].asDouble();
	leashing_command.horizontal_heading_vel = res["horizontal_heading_vel"].asDouble();
	leashing_command.distance_north = res["distance_north"].asDouble();
	leashing_command.distance_north_vel = res["distance_north_vel"].asDouble();
	leashing_command.distance_east = res["distance_east"].asDouble();
	leashing_command.distance_east_vel = res["distance_east_vel"].asDouble();
	leashing_command.horizontal_control_mode = res["horizontal_control_mode"].asInt();
	leashing_command.vertical_distance = res["vertical_distance"].asDouble();
	leashing_command.vertical_distance_vel = res["vertical_distance_vel"].asDouble();
	leashing_command.vertical_control_mode = res["vertical_control_mode"].asInt();
	leashing_command.yaw = res["yaw"].asDouble();
	leashing_command.yaw_vel = res["yaw_vel"].asDouble();
	leashing_command.yaw_control_mode = res["yaw_control_mode"].asInt();
	leashing_command.yawpoint.latitude = res["yawpoint"]["latitude"].asDouble();
	leashing_command.yawpoint.longitude = res["yawpoint"]["longitude"].asDouble();
	leashing_command.yawpoint.altitude = res["yawpoint"]["altitude"].asDouble();

	return true;

}

bool ros_json_parse( Json::Value res, lrs_msgs_common::LeashingStatus & leashing_status ) {

	leashing_status.horizontal_distance = res["horizontal_distance"].asDouble();
	leashing_status.horizontal_heading = res["horizontal_heading"].asDouble();
	leashing_status.distance_north = res["distance_north"].asDouble();
	leashing_status.distance_east = res["distance_east"].asDouble();
	leashing_status.horizontal_control_mode = res["horizontal_control_mode"].asInt();
	leashing_status.vertical_distance = res["vertical_distance"].asDouble();
	leashing_status.vertical_control_mode = res["vertical_control_mode"].asInt();
	leashing_status.yaw = res["yaw"].asDouble();
	leashing_status.yaw_control_mode = res["yaw_control_mode"].asInt();
	leashing_status.yawpoint.latitude = res["yawpoint"]["latitude"].asDouble();
	leashing_status.yawpoint.longitude = res["yawpoint"]["longitude"].asDouble();
	leashing_status.yawpoint.altitude = res["yawpoint"]["altitude"].asDouble();

	return true;

}

bool ros_json_parse( Json::Value m, std_msgs::String & str ) {
  
  //std_msgs::Header header;
  //ros_json_parse (m["header"], header);
  //str.header = header;
  str.data = m["data"].asString();
  
  //cout << "string: "  << str << endl;
  /*
  for (unsigned int i=0; i<m["axes"].size(); i++) {
    joy.axes.push_back (m["axes"][i].asDouble());
  }
  for (unsigned int i=0; i<m["buttons"].size(); i++) {
    joy.buttons.push_back (m["buttons"][i].asInt());
  }
  */
  return true;
}
