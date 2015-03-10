/*
 * online.h
 *
 *  Created on: 2015年2月11日
 *      Author: root
 */

#ifndef ONLINE_H_
#define ONLINE_H_

enum AGENT_TYPE
{
	AGENT_TYPE_UNKNOWN	= 0,	// 未知
	AGENT_TYPE_AGENT		= 1,	// 座席
	AGENT_TYPE_CUSTOM		= 2,	// 客户
};

enum AGENT_STATUS
{
	AGENT_STATUS_UNKNOWN	= 0,	// 未知
	AGENT_STATUS_FREE		= 1,	// 空闲
	AGENT_STATUS_BUSY		= 2,	// 处理中
	AGENT_STATUS_REST		= 3,	// 休息
};

#endif /* ONLINE_H_ */
