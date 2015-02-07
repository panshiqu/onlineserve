/*
 * processer.h
 *
 *  Created on: 2015年2月7日
 *      Author: root
 */

#ifndef PROCESSER_H_
#define PROCESSER_H_

#include "proto/protocol.h"
#include "common/header.h"
#include "common/socketclient.h"

class Processer
{
public:

	SINGLETON_DECLARATION(Processer)

	Processer();
	virtual ~Processer();

	int ProcLogin(SocketClient *pClient, char *pBuffer);
	int ProcLogout(SocketClient *pClient, char *pBuffer);
};

#endif /* PROCESSER_H_ */
