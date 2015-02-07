/*
 * processer.cpp
 *
 *  Created on: 2015年2月7日
 *      Author: root
 */

#include "processer.h"

SINGLETON_IMPLEMENTATION(Processer)

Processer::Processer()
{

}

Processer::~Processer()
{

}

int Processer::ProcLogin(SocketClient *pClient, char *pBuffer)
{
	Login login;
	login.ParseFromString(pBuffer);
	cout << "ProcLogin: " << login.agentid() << endl;
	return true;
}

int Processer::ProcLogout(SocketClient *pClient, char *pBuffer)
{
	cout << "ProcLogout" << endl;
	return true;
}

