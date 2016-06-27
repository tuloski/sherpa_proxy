#include "roszyre.h"



using namespace std;


zyre_t * local_node = 0;
std::string localgroup = "local";
std::map<std::string, std::string> short_name_to_uuid;
std::map<std::string, int> uuid_to_tree_id;
std::map<int, std::string> tree_id_to_uuid;

std::map<std::string, ros::Publisher> camera_pubs;

std::vector<std::string> wasps;


std::string proxy_uuid = "";


//Declare here Publisher
ros::Publisher test_string_pub;
//ros::Publisher multimodal_cmd_pub;
//ros::Publisher interpretation_pub;
ros::Publisher velocity_ctrl_pub;
ros::Publisher leashing_command_pub;
ros::Publisher leashing_status_pub;

void send_forward_all (zmsg_t ** msg) {
  //  ROS_ERROR ("send_forward_all msg");
  //  zyre_shout(local_node, localgroup.c_str(), msg);
  if (proxy_uuid != "") {
    zyre_whisper (local_node, proxy_uuid.c_str(), msg);
  }
}
void send_forward_all (Json::Value content, zframe_t ** frame) {
  Json::Value payload;
  payload["type"] = "to-topic";
  payload["language"] = "JSON";
  payload["content"] = content.toStyledString();

  Json::Value envmsg;
  envmsg["metamodel"] = "sherpa_msgs";
  envmsg["model"] = "";
  envmsg["type"] = "forward-all";
  envmsg["payload"] = payload;

  std::string envstr = envmsg.toStyledString();

  //  ROS_INFO("FORWARD: %s", envstr.c_str());

  zmsg_t * zmsg = zmsg_new ();
  zmsg_pushstr (zmsg, envstr.c_str());

  if (frame != 0) {
    zmsg_append (zmsg, frame);
  }

  send_forward_all (&zmsg);
}

void send_forward_all (Json::Value content) {
  send_forward_all (content, 0);
}

void send_forward_to (std::string to, Json::Value content) {
  send_forward_to (to, content, 0, "");
}

void send_forward_to (std::string to, Json::Value content, std::string forward_to) {
  send_forward_to (to, content, 0, forward_to);
}

void send_forward_to (std::string to, Json::Value content, zframe_t ** frame, std::string forward_to) {
  Json::Value payload;
  payload["type"] = "to-topic";
  payload["language"] = "JSON";
  payload["content"] = content.toStyledString();

  Json::Value envmsg;
  envmsg["metamodel"] = "sherpa_msgs";
  envmsg["model"] = "";
  envmsg["type"] = "forward-to";
  envmsg["forward-to"] = to;
  envmsg["copy-to"] = forward_to;
  envmsg["payload"] = payload;

  std::string envstr = envmsg.toStyledString();

  //  ROS_INFO("FORWARD: %s", envstr.c_str());

  zmsg_t * zmsg = zmsg_new ();
  zmsg_pushstr (zmsg, envstr.c_str());

  if (frame != 0) {
    zmsg_append (zmsg, frame);
  }

  send_forward_to (&zmsg);
}

void send_forward_to (zmsg_t ** msg) {
  if (proxy_uuid != "") {
    zyre_whisper (local_node, proxy_uuid.c_str(), msg);
  }
}


void parse_peers_list (Json::Value jpayload) {

}

void zyre_spin_thread () {

  std::string ns = ros::names::clean (ros::this_node::getNamespace());
  while (!zsys_interrupted) {

    zmsg_t * msg = zyre_recv (local_node);
    if (msg) {
      char *command = zmsg_popstr (msg);
      if (streq (command, "ENTER")) {
        char *peerid = zmsg_popstr (msg);
        char *name = zmsg_popstr (msg);
        std::string ns = ros::names::clean (ros::this_node::getNamespace());
        ROS_INFO("ENTER: %s - %s - %s", ns.c_str(), peerid, name);
        if (strncmp (ns.c_str()+1, name, strlen(name)) == 0) {
          ROS_INFO ("GOT PROXY UUID: %s", peerid);
          proxy_uuid = std::string (peerid);
        }
        free (peerid);
        free (name);
      }

      if (streq (command, "WHISPER")) {
        char *peerid = zmsg_popstr (msg);
        char *name = zmsg_popstr (msg);
        char *message = zmsg_popstr (msg);
        //	ROS_INFO("WHISPER: %s - %s - %s", peerid, name, message);

        Json::Value root;
        Json::Reader reader;
        bool parse_flag = reader.parse(message, root, false);

        if (!parse_flag) {
          ROS_ERROR ("COULD NOT PARSE JSON STRING: %s", reader.getFormatedErrorMessages().c_str());
        }

        std::string type = root["type"].asString();

        if (type == "peer-list") {
          //	short_name_to_uuid.clear();
          Json::Value jpayload = root["payload"];
          for (unsigned int i=0; i<jpayload.size(); i++) {
            ROS_INFO("PEER: %s", jpayload[i].toStyledString().c_str());
            std::string short_name = jpayload[i]["short-name"].asString();
            std::string long_name = jpayload[i]["long-name"].asString();
            std::string uuid = jpayload[i]["peerid"].asString();
            ROS_INFO("PEER UNPACKED: %s - %s - %s", short_name.c_str(), long_name.c_str(), 
            uuid.c_str());
            short_name_to_uuid[short_name] = uuid;
          }
        }

        free (peerid);
        free (name);
        free (message);
      }

      if (streq (command, "SHOUT")) {
        size_t size = zmsg_size(msg);
        assert ((size == 4) || (size == 5));
        char *peerid = zmsg_popstr (msg);
        char *name = zmsg_popstr (msg);
        char *group = zmsg_popstr (msg);
        char *message = zmsg_popstr (msg);

        //	ROS_INFO("SHOUT: %s - %s - %s - %s", peerid, name, group, message);

        Json::Value root;
        Json::Reader reader;
        bool parse_flag = reader.parse(message, root, false);

        if (!parse_flag) {
          ROS_ERROR ("roszyre: COULD NOT PARSE JSON STRING: %s", reader.getFormatedErrorMessages().c_str());
        }

        std::string type = root["type"].asString();
        std::string language = root["language"].asString();
        if (type != "to-topic") {
          ROS_INFO("MSG TYPE: %s", type.c_str());
        }
        //      ROS_INFO("MSG LANGUAGE: %s", language.c_str());

        if (type == "peer-list") {
          Json::Value jpayload = root["payload"];
          for (unsigned int i=0; i<jpayload.size(); i++) {
            ROS_INFO("PEER: %s", jpayload[i].toStyledString().c_str());
          }
        }

        if (type == "to-topic") {
          Json::Value rmsg;
          Json::Reader reader;
          bool parse_flag = reader.parse(root["content"].asString(), rmsg, false);

          if (!parse_flag) {
            ROS_ERROR ("roszyre: COULD NOT PARSE JSON STRING: %s", 
            reader.getFormatedErrorMessages().c_str());
          }

          std::string topic = rmsg["topic-name"].asString();

          Json::Value jmsg = rmsg["msg"];

          //ROS_ERROR ("Index: %d ", distance(camera_pubs.begin(), camera_pubs.find(topic)) );
          if (camera_pubs.find (topic) != camera_pubs.end() && wasps[distance(camera_pubs.begin(), camera_pubs.find(topic))] != ns) {
        	  camera_handler_sherpa::Camera cam;
			  if (ros_json_parse (jmsg, cam)) {
				  camera_pubs[topic].publish (cam);
			  } else {
				  ROS_ERROR ("Could not parse json to Camera");
			  }
		  }

          if (topic == "/wasp/vel_ctrl") {
        	  geometry_msgs::Twist msg_twist;
			  if (ros_json_parse (jmsg, msg_twist)) {
				  velocity_ctrl_pub.publish( msg_twist );
			  }
			  else {
				ROS_ERROR ("Could not parse json to twist");
			  }
		  }

          else if (topic == "/CREATE/leashing_command") {
        	  lrs_msgs_common::LeashingCommand leashing_command;
			  if (ros_json_parse (jmsg, leashing_command)) {
				  leashing_command_pub.publish( leashing_command );
			  }
			  else {
				ROS_ERROR ("Could not parse json to leashing command");
			  }
		  }

          else if (topic == "/wasp/leashing_status") {
			  lrs_msgs_common::LeashingStatus leashing_status;
			  if (ros_json_parse (jmsg, leashing_status)) {
				  leashing_status_pub.publish( leashing_status );
			  }
			  else {
				ROS_ERROR ("Could not parse json to leashing status");
			  }
		  }

          /*if (topic == "/CREATE/test_string") {
            
            std_msgs::String msg_string;
            if (ros_json_parse (jmsg, msg_string)) {              
              test_string_pub.publish( msg_string );
            } 
            else {
              ROS_ERROR ("Could not parse json to Joy");
            }
          }*/

          /*else if( topic == "/CREATE/multimodal_cmd") {
            mhri_msgs::multimodal_action cmd;
            if (ros_json_parse (jmsg, cmd)) {              
              multimodal_cmd_pub.publish( cmd );
            } 
            else {
              ROS_ERROR ("Could not parse multimodal command");
            }
          }*/

          /*else if( topic == "/UNIBH/interpretation") {
            mhri_msgs::multimodal cmd;
            if (ros_json_parse (jmsg, cmd)) {              
              interpretation_pub.publish( cmd );
            } 
            //else {
            //  ROS_ERROR ("Could not parse interpretation command");
            //}
          }*/
        }
        free (peerid);
        free (name);
        free (message);
        free (group);
      }
      free (command);
      zmsg_destroy (&msg);
    }
  }
}



void send_peers_request () {

  Json::Value json;
  json["type"] = "empty";
  json["language"] = "NONE";
  json["content"] = "";

  Json::Value envmsg;
  envmsg["metamodel"] = "sherpa_msgs";
  envmsg["model"] = "";
  envmsg["type"] = "peers";
  envmsg["payload"] = json;

  std::string envstr = envmsg.toStyledString();
  ROS_INFO("%s", envstr.c_str());
  zyre_shouts(local_node, localgroup.c_str(), "%s", envstr.c_str());
}


void send_create_team (Json::Value payload) {
  Json::Value envmsg;
  envmsg["metamodel"] = "sherpa_msgs";
  envmsg["model"] = "";
  envmsg["type"] = "create-team";
  envmsg["payload"] = payload;

  std::string envstr = envmsg.toStyledString();
  ROS_INFO("%s", envstr.c_str());
  zyre_shouts(local_node, localgroup.c_str(), "%s", envstr.c_str());
}

void send_create_team_example () {
  Json::Value jpayload;
  jpayload["team"] = "team4711";
  jpayload["members"][0] = short_name_to_uuid["RMAX1"];
  jpayload["members"][1] = short_name_to_uuid["operator1"];
  send_create_team (jpayload);
}



int main(int argc, char** argv) {

  int major, minor, patch;
  zyre_version (&major, &minor, &patch);
  assert (major == ZYRE_VERSION_MAJOR);
  assert (minor == ZYRE_VERSION_MINOR);
  assert (patch == ZYRE_VERSION_PATCH);


  ros::init(argc, argv, "create_roszyre");
  ros::NodeHandle n;

  std::string ns = ros::names::clean (ros::this_node::getNamespace());
  
  //Declare here the publishers and subscribers
  //test_string_pub = n.advertise<std_msgs::String>("/CREATE/test_string", 0);
  //multimodal_cmd_pub = n.advertise<mhri_msgs::multimodal_action>("/CREATE/multimodal_cmd", 0);
  //interpretation_pub = n.advertise<mhri_msgs::multimodal>("/UNIHB/interpretation", 0);
  velocity_ctrl_pub = n.advertise<geometry_msgs::Twist>("/wasp/vel_ctrl/proxy", 0);
  leashing_command_pub = n.advertise<lrs_msgs_common::LeashingCommand>("/CREATE/leashing_command", 0);
  leashing_status_pub = n.advertise<lrs_msgs_common::LeashingStatus>("/wasp/leashing_status", 0);
  
  //ros::Subscriber test_string_sub =    n.subscribe("/CREATE/test_string/proxy", 1000, test_string_callback);
  //ros::Subscriber multimodal_cmd_sub = n.subscribe("/CREATE/multimodal_cmd/proxy", 1000, multimodal_cmd_cb );
  //ros::Subscriber interpretation_sub = n.subscribe("/UNIHB/interpretation/proxy", 1000, interpretation_cb );
  ros::Subscriber camera_sub = n.subscribe("camera_published", 100, camera_callback );
  ros::Subscriber velocity_ctrl_sub = n.subscribe("/wasp/vel_ctrl", 100, operator_control_velocity_callback );
  ros::Subscriber leashing_command_sub = n.subscribe("/CREATE/leashing_command/proxy", 100, leashing_command_callback );
  ros::Subscriber leashing_status_sub = n.subscribe("/wasp/leashing_status/proxy", 100, leashing_status_callback );

  //TODO don't like this fixed list of agents
  wasps.push_back("/wasp0");
  wasps.push_back("/wasp1");
  wasps.push_back("/wasp2");

    //ros::param::get("/agents", agents);	//to get a different list of agents from params
    for (unsigned int i=0; i<wasps.size(); i++) {
      std::string topic = wasps[i] + "/camera_published";
      ROS_ERROR ("Index: %d ", distance(camera_pubs.begin(), camera_pubs.find(topic)) );
      if (wasps[i] != ns)
    	  camera_pubs[topic] = n.advertise<camera_handler_sherpa::Camera>(topic, 1);
    }

  std::string name = "lq0";
  if (ns != "") {
    name = ns.substr(1,-1);
  }
	
  bool use_gossip = true;

  std::string gossip = "ipc:///tmp/" + name + "-hub";
  std::string endpoint = "ipc:///tmp/" + name + "-roszyre";


  ROS_INFO("NAMESPACE: %s", ns.c_str());
  ROS_INFO("NAME: %s", name.c_str());
  ROS_INFO("GOSSIP HUB: %s", gossip.c_str());
  ROS_INFO("LOCAL GROUP: %s", localgroup.c_str());

  local_node = zyre_new ("roszyre");
  assert (local_node);
  assert (streq (zyre_name (local_node), "roszyre"));
  //  zyre_set_verbose (local_node);

  zyre_set_header(local_node, "type", "%s", "roszyre");

  int rc;

  if (use_gossip) {
    rc = zyre_set_endpoint (local_node, "%s", endpoint.c_str());
    assert (rc == 0);
    zyre_gossip_connect (local_node, "%s", gossip.c_str());
  }

  zyre_dump (local_node);

  rc = zyre_start (local_node);
  assert (rc == 0);

  zyre_join(local_node, localgroup.c_str());   

  zclock_sleep (100);

  zyre_dump (local_node);

  boost::thread sthread (zyre_spin_thread);    

  ROS_INFO("Spinning roszyre");

  int counter = 0;
  ros::Rate loop_rate(100);

  while (!zsys_interrupted) {
  

    ros::spinOnce();

    counter++;
    loop_rate.sleep();
  }  

  zyre_stop (local_node);

  zyre_destroy (&local_node);

  return 0;
}
