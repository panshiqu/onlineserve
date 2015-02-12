/*
 * dispatcher.cpp
 *
 *  Created on: 2015年1月26日
 *      Author: root
 */

#include "dispatcher.h"
#include "processor.h"

Dispatcher::Dispatcher()
{

}

Dispatcher::~Dispatcher()
{

}

void Dispatcher::Dispatch(void)
{
	// 注册处理回调函数
	Processor::GetInstance().RegisterCallback();

	// 创建启动服务
	SocketServer server(this);
	server.Init(11111);
	server.Run();
}

void Dispatcher::OnConnected(SocketClient *pClient)
{
	cout << "OnConnected." << endl;
}

void Dispatcher::OnDisconnected(SocketClient *pClient)
{
	cout << "OnDisconnected." << endl;
}

void Dispatcher::OnConnectFailed(SocketClient *pClient)
{
	cout << "OnConnectFailed." << endl;
}

void Dispatcher::OnMessage(char *pMessage, SocketClient *pClient)
{
	// 取消息头
	Header *pHeader = (Header *)pMessage;

	// 查找处理器
	map<int, Callback>::iterator itr = m_mapCallback.find(pHeader->nCommand);
	if (itr == m_mapCallback.end()) pHeader->nCommand = UNKNOWN;

	// 取消息体分发
	char *pProto = &pMessage[sizeof(Header)];
	int nLength = pHeader->nLength - sizeof(Header);
	cout << "##Receive CMD: " << pHeader->nCommand << " Length: " << nLength << " ERR: " << pHeader->nErrorCode << endl;
	int nRes = m_mapCallback[pHeader->nCommand](pProto, nLength, pClient);

	// 出错直接回复
	if (nRes != E_SUCCEED)
		pClient->SendMessage("", 0, pHeader->nCommand, nRes);

	// 释放删除消息
	delete pMessage;
}

