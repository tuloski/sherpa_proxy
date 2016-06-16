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
