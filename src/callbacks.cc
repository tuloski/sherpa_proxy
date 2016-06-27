#include "callbacks.h"


using namespace std;  


//---Callback /CREATE/test_string_proxy topic: [Topic -> Json]
void test_string_callback (const ros::MessageEvent<std_msgs::String const>& event) {
  
  const std::string& publisher_name = event.getPublisherName();
  std::string ns = ros::names::clean (ros::this_node::getNamespace());
  if (publisher_name == ns + "/roszyre") return;

  const std_msgs::StringConstPtr& msg = event.getMessage();

  Json::Value jmsg;
  jmsg["topic-name"] = "/CREATE/test_string";
  jmsg["msg"] = get_json_value (*msg);
    
  send_forward_all( jmsg );
}

void camera_callback (const ros::MessageEvent<camera_handler_sherpa::Camera const>& event) {

  const std::string& publisher_name = event.getPublisherName();
  std::string ns = ros::names::clean (ros::this_node::getNamespace());
  if (publisher_name == ns + "/roszyre") return;

  const camera_handler_sherpa::CameraConstPtr& msg = event.getMessage();

  Json::Value jmsg;
  jmsg["topic-name"] = ns + "/camera_published";
  jmsg["msg"] = get_json_value (*msg);

  send_forward_all( jmsg );
}

void operator_control_velocity_callback (const ros::MessageEvent<geometry_msgs::Twist const>& event) {

  const std::string& publisher_name = event.getPublisherName();
  std::string ns = ros::names::clean (ros::this_node::getNamespace());
  if (publisher_name == ns + "/roszyre") return;

  const geometry_msgs::TwistConstPtr& msg = event.getMessage();

  Json::Value jmsg;
  jmsg["topic-name"] = "/wasp/vel_ctrl";
  jmsg["msg"] = get_json_value(*msg);

  send_forward_all( jmsg );
}

void leashing_command_callback (const ros::MessageEvent<lrs_msgs_common::LeashingCommand const>& event) {

  const std::string& publisher_name = event.getPublisherName();
  std::string ns = ros::names::clean (ros::this_node::getNamespace());
  if (publisher_name == ns + "/roszyre") return;

  const lrs_msgs_common::LeashingCommandConstPtr& msg = event.getMessage();

  Json::Value jmsg;
  jmsg["topic-name"] = "/CREATE/leashing_command";
  jmsg["msg"] = get_json_value(*msg);

  send_forward_all( jmsg );
}

void leashing_status_callback (const ros::MessageEvent<lrs_msgs_common::LeashingStatus const>& event) {

  const std::string& publisher_name = event.getPublisherName();
  std::string ns = ros::names::clean (ros::this_node::getNamespace());
  if (publisher_name == ns + "/roszyre") return;

  const lrs_msgs_common::LeashingStatusConstPtr& msg = event.getMessage();

  Json::Value jmsg;
  jmsg["topic-name"] = "/wasp/leashing_status";
  jmsg["msg"] = get_json_value(*msg);

  send_forward_all( jmsg );
}

/*void multimodal_cmd_cb ( const ros::MessageEvent<mhri_msgs::multimodal_action const>& event) {

  const std::string& publisher_name = event.getPublisherName();
  std::string ns = ros::names::clean (ros::this_node::getNamespace());
  if (publisher_name == ns + "/roszyre") return;

  const mhri_msgs::multimodal_actionConstPtr& msg = event.getMessage();

	Json::Value jmsg;
  jmsg["topic-name"] = "/CREATE/multimodal_cmd";
  jmsg["msg"] = get_json_value (*msg);
    
	send_forward_to ("op1", jmsg);

}*/

/*void interpretation_cb ( const ros::MessageEvent<mhri_msgs::multimodal const>& event) {

  const std::string& publisher_name = event.getPublisherName();
  std::string ns = ros::names::clean (ros::this_node::getNamespace());
  if (publisher_name == ns + "/roszyre") return;

  const mhri_msgs::multimodalConstPtr& msg = event.getMessage();

	Json::Value jmsg;
  jmsg["topic-name"] = "/UNIBH/interpretation";
  jmsg["msg"] = get_json_value (*msg);
    
  cout << "jmsg: " << endl << jmsg << endl;

	send_forward_to ("op0", jmsg);

}*/

