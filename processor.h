/*
 * processor.h
 *
 *  Created on: 2015年2月9日
 *      Author: root
 */

#ifndef PROCESSOR_H_
#define PROCESSOR_H_

#include "base/header.h"
#include "proto/protocol.h"
#include "base/socketclient.h"

class Processor
{
private:
	Processor();
	virtual ~Processor();

public:
	SINGLETON(Processor)
	void RegisterCallback(void);

	/*
	 * 系统消息操作
	 */
	void ProcUnknown(char *pMessage, int nLength, SocketClient *pClient);
	void ProcListening(char *pMessage, int nLength, SocketClient *pClient);

	/*
	 * 座席相关消息操作
	 */
	void ProcAgentLogin(char *pMessage, int nLength, SocketClient *pClient);
	void ProcAgentLogout(char *pMessage, int nLength, SocketClient *pClient);
};

#endif /* PROCESSOR_H_ */
