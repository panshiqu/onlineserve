/*
 * main.cpp
 *
 *  Created on: 2015年2月11日
 *      Author: root
 */

#include <stdio.h>
#include <stdlib.h>

#include "agentdelegate.h"

int main(void)
{
	AgentDelegate delegate;
	SocketClient agent(&delegate);
	agent.Init("127.0.0.1", 11111);

	while (agent.Run())
	{
		cout << "input cmd:";

		int cmd;
		scanf("%d", &cmd);

		switch (cmd)
		{
		case AGENT_LOGIN:
			{
				cout << "format as aid:";

				int nID;
				scanf("%d", &nID);

				ReqAgentLogin req;
				req.set_aid(nID);

				char szMessage[req.ByteSize()];
				req.SerializeToArray(szMessage, req.ByteSize());
				agent.SendMessage(szMessage, req.ByteSize(), cmd, 0);
			}
			break;

		case AGENT_LOGOUT:
			{
				cout << "format as aid:";

				int nID;
				scanf("%d", &nID);

				ReqAgentLogout req;
				req.set_aid(nID);

				char szMessage[req.ByteSize()];
				req.SerializeToArray(szMessage, req.ByteSize());
				agent.SendMessage(szMessage, req.ByteSize(), cmd, 0);
			}
			break;

		case AGENT_CHAT:
			{
				cout << "format as aid,ato,word:";

				int nAgentID;
				int nAgentTO;
				char szWord[128] = {0};
				scanf("%d,%d,%s", &nAgentID, &nAgentTO, szWord);

				ReqAgentChat req;
				req.set_aid(nAgentID);
				req.set_ato(nAgentTO);
				req.set_word(szWord);

				char szMessage[req.ByteSize()];
				req.SerializeToArray(szMessage, req.ByteSize());
				agent.SendMessage(szMessage, req.ByteSize(), cmd, 0);
			}
			break;

		case AGENT_REQUEST:
			{
				cout << "format as aid:";

				int nAgentID;
				scanf("%d", &nAgentID);

				ReqAgentRequest req;
				req.set_aid(nAgentID);

				char szMessage[req.ByteSize()];
				req.SerializeToArray(szMessage, req.ByteSize());
				agent.SendMessage(szMessage, req.ByteSize(), cmd, 0);
			}
			break;

		default:
			break;
		}
	}
}


