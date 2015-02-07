/*
 * dispatcher.cpp
 *
 *  Created on: 2015年1月26日
 *      Author: root
 */

#include "dispatcher.h"

SINGLETON_IMPLEMENTATION(Dispatcher)

Dispatcher::Dispatcher()
{

}

Dispatcher::~Dispatcher()
{

}

void Dispatcher::Register(int command, MessageCallback& callback)
{
	m_mapCallback[command] = callback;
}

