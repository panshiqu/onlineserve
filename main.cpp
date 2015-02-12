/*
 * main.cpp
 *
 *  Created on: 2015年1月21日
 *      Author: root
 */


#include "dispatcher.h"

using namespace std;

int main(void)
{
	Dispatcher::GetInstance().Dispatch();
	return 0;
}

