/*
 * dispatcher.cpp
 *
 *  Created on: 2015年1月26日
 *      Author: root
 */

#include "dispatcher.h"

Dispatcher::Dispatcher()
{

}

Dispatcher::~Dispatcher()
{

}

Dispatcher &Dispatcher::GetInstance(void)
{
	static Dispatcher instance;
	return instance;
}

void Dispatcher::Register(Observer *pObserver)
{

}

void Dispatcher::UnRegister(Observer *pObserver)
{

}

void Dispatcher::AddMessage(char *pBuffer)
{

}

void Dispatcher::Dispatch(void)
{

}

