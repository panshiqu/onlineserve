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
	UNKNOWN			= 0,		// 未知
	LISTENING		= 1,		// 监听

	// 座席消息
	AGENT_LOGIN		= 101,	// 登陆
	AGENT_LOGOUT	= 102,	// 登出
	AGENT_CHAT		= 103,	// 发起聊天
	AGENT_REQUEST	= 104,	// 请求座席

	// 服务器消息
	SRV_AGENT_CHAT	= 501,	// 转发聊天
};

enum ERROR_CODE
{
	E_SUCCEED			= 0,		// 成功
	E_ILLEGAL			= 1,		// 非法

	// 座席相关
	E_AGENT_LOGIN		= 101,	// 重复登陆
	E_AGENT_LOGOUT		= 102,	// 重复退出
	E_AGENT_FIND		= 103,	// 座席未找到
};

#endif /* PROTO_PROTOCOL_H_ */
