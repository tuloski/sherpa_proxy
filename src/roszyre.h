#ifndef _ROSZYRE_H
#define _ROSZYRE_H

#include "ros/ros.h"
#include <uuid/uuid.h>
#include "zyre.h"
#include "rosjsonparse.h"
#include "getjsonvalue.h"
#include "callbacks.h"
#include <jsoncpp/json/writer.h>
#include <boost/thread.hpp>
#include <map>

void send_forward_all (Json::Value content);
void send_forward_all (Json::Value content, zframe_t ** frame);
void send_forward_all (zmsg_t ** msg);

void send_forward_to (std::string to, Json::Value content);
void send_forward_to (std::string to, Json::Value content, std::string forward_to);
void send_forward_to (std::string to, Json::Value content, zframe_t ** frame, std::string forward_to);
void send_forward_to (zmsg_t ** msg);
void zyre_spin_thread ();


#endif
