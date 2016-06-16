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

