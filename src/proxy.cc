#include "ros/ros.h"

#include <boost/thread.hpp>

#include <jsoncpp/json/writer.h>
#include <jsoncpp/json/json.h>

#include <map>

#include "zyre.h"

zyre_t *local_node = 0;
zyre_t *remote = 0;
std::string short_name = "";

std::string remotegroup = "remote";
std::string localgroup = "local";

std::map<std::string, std::string> name_to_uuid;
std::map<std::string, std::string> remote_name_to_uuid;

using namespace std;
void zyre_spin_remote () {

	while (!zsys_interrupted) {
		zmsg_t * msg = zyre_recv (remote);
		if (msg) {
			
			char *command = zmsg_popstr (msg);
			//ROS_INFO("REMOTE COMMAND: %s", command);

			if (streq (command, "ENTER")) {
				char *peerid = zmsg_popstr (msg);
				char *name = zmsg_popstr (msg);
				ROS_INFO("REMOTE ENTER: %s - %s", peerid, name);
				remote_name_to_uuid[name] = peerid;
				free (peerid);
				free (name);
			}

			if (streq (command, "EXIT")) {
				char *peerid = zmsg_popstr (msg);
				char *name = zmsg_popstr (msg);
				ROS_INFO("REMOTE EXIT: %s - %s", peerid, name);
				free (peerid);
				free (name);
			}

			if (streq (command, "JOIN")) {
				char *peerid = zmsg_popstr (msg);
				char *name = zmsg_popstr (msg);
				char *groupname = zmsg_popstr (msg);
				char * longname = zyre_peer_header_value (remote, peerid, "long-name");
				ROS_INFO("JOIN: %s - %s - %s - %s", peerid, name, groupname, longname);
				free (peerid);
				free (name);
				free (groupname);
			}

			if (streq (command, "LEAVE")) {
				char *peerid = zmsg_popstr (msg);
				char *name = zmsg_popstr (msg);
				char *groupname = zmsg_popstr (msg);
				ROS_INFO("LEAVE: %s - %s - %s", peerid, name, groupname);
				free (peerid);
				free (name);
				free (groupname);
			}

			if (streq (command, "SHOUT") || streq (command, "WHISPER")) {
				size_t size_without_frame = 3;
				size_t size = zmsg_size(msg);
				char *peerid = zmsg_popstr (msg);
				char *name = zmsg_popstr (msg);
				char *group = 0;
				if (streq (command, "SHOUT")) {
					group = zmsg_popstr (msg);
					size_without_frame = 4;
				}

			assert ((size == size_without_frame) || (size == size_without_frame+1));
		char *message = zmsg_popstr (msg);

		if (streq (command, "SHOUT")) {
			// ROS_INFO("REMOTE SHOUT: %s - %s - %s - %s", peerid, name, group, message);
		}

		if (streq (command, "WHISPER")) {
			//	  ROS_INFO("REMOTE WHISPER: %s - %s", peerid, name);
		}

		Json::Value root;
		Json::Reader reader;
		bool parse_flag = reader.parse(message, root, false);

		if (!parse_flag) {
			ROS_ERROR ("COULD NOT PARSE JSON STRING: %s", reader.getFormatedErrorMessages().c_str());
		}

		std::string type = root["type"].asString();
		if ((type != "forward-all") && (type != "forward-to")) {
			ROS_ERROR("REMOTE MSG TYPE: %s", type.c_str());
		}	

		Json::Value jpayload = root["payload"];
		//ROS_INFO("PAYLOAD TYPE: %s", jpayload["type"].asString().c_str());
		//ROS_INFO("%s", jpayload.toStyledString().c_str());

		// Whatever it gets it shouts the payload to the local group


		// Check if copy needed

			if (streq (command, "WHISPER")) {
			std::string to = root["forward-to"].asString();
			std::string copy_to = root["copy-to"].asString();
			if (copy_to != "") {
				if (short_name != copy_to) {
					//	      ROS_ERROR ("MYSELF - TO - COPY TO: %s - %s - %s", short_name.c_str(), to.c_str(), copy_to.c_str());
					if (remote_name_to_uuid.find(copy_to) != remote_name_to_uuid.end()) {
						if (size == size_without_frame) {
							zyre_whisper(remote, remote_name_to_uuid[copy_to].c_str(), &msg);
						} 
						else {
							zmsg_t * zmsg = zmsg_new ();
							//		  zmsg_pushstr (zmsg, jpayload.toStyledString().c_str());
							zmsg_pushstr (zmsg, message);
							zframe_t * frame = zmsg_last(msg);
							assert (frame != 0);
							zframe_t * newframe = zframe_dup(frame);
							zmsg_append (zmsg, &newframe);	    
							zyre_whisper(remote, remote_name_to_uuid[copy_to].c_str(), &zmsg);
						}
					}
				}
			}
		}	


		if (size == size_without_frame) {
		  zyre_shouts(local_node, localgroup.c_str(), "%s", jpayload.toStyledString().c_str());		  
		} 
		else {
		  zmsg_t * zmsg = zmsg_new ();
		  zmsg_pushstr (zmsg, jpayload.toStyledString().c_str());
		  zframe_t * frame = zmsg_last(msg);
		  assert (frame != 0);
		  zframe_t * newframe = zframe_dup(frame);
		  zmsg_append (zmsg, &newframe);	    
		  zyre_shout(local_node, localgroup.c_str(), &zmsg);
		}
		free (peerid);
		free (name);
		free (group);
		free (message);
      }
      free (command);
      zmsg_destroy (&msg);
      
    }
  }
}

void zyre_spin_local () {
	while (!zsys_interrupted) {

		cout << "while" << endl;
		zmsg_t * msg = zyre_recv (local_node);
		if (msg) {
			char *command = zmsg_popstr (msg);
			ROS_INFO("LOCAL COMMAND: %s", command);

			if (streq (command, "ENTER")) {
				char *peerid = zmsg_popstr (msg);
				char *name = zmsg_popstr (msg);
				ROS_INFO("LOCAL ENTER: %s - %s", peerid, name);
				free (peerid);
				free (name);
			}

			if (streq (command, "EXIT")) {
				char *peerid = zmsg_popstr (msg);
				char *name = zmsg_popstr (msg);
				ROS_INFO("LOCAL EXIT: %s - %s", peerid, name);
				free (peerid);
				free (name);
			}

			if (streq (command, "SHOUT") || streq (command, "WHISPER")) {
				
				cout << "WHISPER or SHOUT" << endl;
				ROS_ERROR ("SIZE: %zd", zmsg_size(msg)); 
				size_t size_without_frame = 3;
				size_t size = zmsg_size(msg);
				char *peerid = zmsg_popstr (msg);
				char *name = zmsg_popstr (msg);
				char *group = 0;
				if (streq (command, "SHOUT")) {
					group = zmsg_popstr (msg);
					size_without_frame = 4;
				}
				assert ((size == size_without_frame) || (size == size_without_frame+1));

				char *message = zmsg_popstr (msg);
				ROS_INFO("SHOUT: %s - %s - %s - %s", peerid, name, group, message);

	
				Json::Value root;
				Json::Reader reader;
				bool parse_flag = reader.parse(message, root, false);

				//cout << "parse_flag: " << parse_flag << endl;

				if (!parse_flag) {
					ROS_ERROR ("COULD NOT PARSE JSON STRING: %s", reader.getFormatedErrorMessages().c_str());
				}

				std::string type = root["type"].asString();
				cout << "type: " << type << endl;

				if ((type != "forward-all") && (type != "forward-to")) {
					ROS_INFO("LOCAL MSG TYPE: %s", type.c_str());
				}
				if (type == "forward-all") {
					
					cout << "forward all" << endl;

					if (size == size_without_frame) {
						cout << "size_without_frame" << endl;
						zyre_shouts(remote, remotegroup.c_str(), "%s", message);
						cout << "after zyre" << endl;
					} 
					else {
						zmsg_t * zmsg = zmsg_new ();
						zmsg_pushstr (zmsg, message);
						zframe_t * frame = zmsg_last(msg);
						assert (frame != 0);
						zframe_t * newframe = zframe_dup(frame);
						zmsg_append (zmsg, &newframe);	    
						zyre_shout(remote, remotegroup.c_str(), &zmsg);
					}
					
				}

				if (type == "forward-to") {
					std::string to = root["forward-to"].asString();
					//	  ROS_ERROR("forward-to: %s", to.c_str());
					if (remote_name_to_uuid.find(to) != remote_name_to_uuid.end()) {
						// ROS_ERROR ("remote forward to: %s", to.c_str());
						zmsg_t * zmsg = zmsg_new ();
						zmsg_pushstr (zmsg, message);
						if (size != size_without_frame) {
							zframe_t * frame = zmsg_last(msg);
							assert (frame != 0);
							zframe_t * newframe = zframe_dup(frame);
							zmsg_append (zmsg, &newframe);	    
						}
						zyre_whisper(remote, remote_name_to_uuid[to].c_str(), &zmsg);	      	    
					}
				}
				if (type == "execution-tst") { // In KUL program should be handled by world model
					ROS_ERROR("SHOUT MSG TYPE: %s - %s", type.c_str(), remotegroup.c_str());
					zyre_shouts(remote, remotegroup.c_str(), "%s", message);
				}

				if (type == "update-execution-tst-node") { // In KUL program should be handled by world model
					ROS_ERROR("SHOUT MSG TYPE: %s - %s", type.c_str(), remotegroup.c_str());
					zyre_shouts(remote, remotegroup.c_str(), "%s", message);
				}

				free (peerid);
				free (name);
				free (group);
				free (message);
				
			}
			free (command);
			zmsg_destroy (&msg);
		}
	} 	 
}

int main(int argc, char** argv) {

  ros::init(argc, argv, "proxy", ros::init_options::AnonymousName);
  ros::NodeHandle n;

  std::string ns = ros::names::clean (ros::this_node::getNamespace());

  std::string name = "rmax0";
  if (ns != "") {
    name = ns.substr(1,-1);
  }
  std::string gossip = "ipc:///tmp/" + name + "-hub";
  std::string endpoint = "ipc:///tmp/" + name + "-proxy";

  ROS_INFO("NAMESPACE: %s", ns.c_str());
  ROS_INFO("NAME: %s", name.c_str());
  ROS_INFO("GOSSIP HUB: %s", gossip.c_str());
  ROS_INFO("LOCAL GROUP: %s", localgroup.c_str());
  ROS_INFO("REMOTE GROUP: %s", remotegroup.c_str());

  local_node = zyre_new (name.c_str());
  remote = zyre_new (name.c_str());
  assert (local_node);
  assert (remote);
  assert (streq (zyre_name (local_node), name.c_str()));
  //  zyre_set_verbose (remote);
  //  zyre_set_verbose (local_node);

  zyre_set_header(local_node, "type", "%s", "proxy");

  std::string type = "hawk";

  std::string capabilities = "[\"fly-to\", \"scan-ground-single\", \"init-collect-data\", \"stop-collect-data\", \"analyse-data\", \"yaw\", \"inform-collect-data\"]";
  

  short_name = name;
  ros::param::get ("~short_name", short_name);

  std::string long_name = "http://www.ida.liu.se/aiics/" + short_name; // unique name

  ros::param::get ("~long_name", long_name);

  ROS_INFO("SHORT NAME: %s", short_name.c_str());
  ROS_INFO("LONG NAME: %s", long_name.c_str());

  zyre_set_header(remote, "type", "%s", type.c_str()); // genius, donkey, wasp, hawk
  zyre_set_header(remote, "short-name", "%s", short_name.c_str());
  zyre_set_header(remote, "long-name", "%s", long_name.c_str());
  zyre_set_header(remote, "capabilities", "%s", capabilities.c_str());

  int rc = zyre_set_endpoint(local_node, "%s", endpoint.c_str());
  assert (rc == 0);

  //  zyre_gossip_connect (node, gossip.c_str());

  zyre_gossip_bind(local_node, "%s", gossip.c_str());

  rc = zyre_start (local_node);
  assert (rc == 0);

  rc = zyre_start (remote);
  assert (rc == 0);

  zyre_join(local_node, localgroup.c_str());
  zyre_join (remote, remotegroup.c_str());

  boost::thread lthread (zyre_spin_local);
  boost::thread rthread (zyre_spin_remote);

  ROS_INFO("Looping proxy");

  while (!zsys_interrupted) {
    usleep(10000);
  }  

  zyre_stop (local_node);
  zyre_stop (remote);

  zyre_destroy (&local_node);
  zyre_destroy (&remote);

  return 0;
}
