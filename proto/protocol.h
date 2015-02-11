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

enum COMMAND_TYPE {
	UNKNOWN			= 0,
	LISTENING		= 1,

	AGENT_LOGIN		= 2,
	AGENT_LOGOUT	= 3,
};

enum ERROR_CODE
{
	ERROR_SUCCEED		= 0,		// 成功
	ERROR_ILLEGAL		= 1,		// 非法

	// 座席相关
	ERROR_AGENT_LOGIN	= 101,	// 重复登陆
};

#endif /* PROTO_PROTOCOL_H_ */
