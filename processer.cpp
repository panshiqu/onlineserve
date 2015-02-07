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

int Processer::ProcLogin(void)
{
	return true;
}

int Processer::ProcLogout(void)
{
	return true;
}

