/*
 * protocol.h
 *
 *  Created on: 2015年2月7日
 *      Author: root
 */

#ifndef PROTO_PROTOCOL_H_
#define PROTO_PROTOCOL_H_

#include "comm.pb.h"

using namespace comm;

enum PROTOCOL_TYPE {
	UNKNOWN			= 0,
	LISTEN				= 1,

	AGENT_LOGIN		= 2,
	AGENT_LOGOUT		= 3,
};



#endif /* PROTO_PROTOCOL_H_ */
