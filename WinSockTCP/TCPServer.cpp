#include "stdafx.h"
#include "TCPServer.h"

TCPServer::TCPServer()
{
	m_wsa = { 0 };
	m_serverAddr = { 0 };
	m_clientAddr = { 0 };
	m_ServerState = false;
	memset(&m_buffer, 0x00, sizeof(m_buffer));
	m_ServerState = onInitialize();
}

TCPServer::~TCPServer()
{
	closesocket(m_client);
	closesocket(m_server);
	WSACleanup();

}

int TCPServer::onInitialize()
{
	int ret;
	if (WSAStartup(MAKEWORD(2, 2), &m_wsa) != 0)
		return ERROR_SERVER;

	m_server = socket(AF_INET, SOCK_STREAM, 0);
	if (m_server == INVALID_SOCKET)
		return ERROR_SERVER;

	m_serverAddr.sin_family = AF_INET;
	m_serverAddr.sin_addr.s_addr = htonl(INADDR_ANY);
	m_serverAddr.sin_port = htons(PORT);
	
	ret = bind(m_server, (SOCKADDR*)&m_serverAddr, sizeof(m_serverAddr));
	if (ret == SOCKET_ERROR)
		return ERROR_SERVER;

	ret = listen(m_server, 1);
	if (ret == SOCKET_ERROR)
		return ERROR_SERVER;

	return SUCCESS_SERVER;
}

int TCPServer::onCommunication()
{
	
	if (m_ServerState)
	{
		while (1)
		{
			//try client connection 
			int addrLength = sizeof(m_clientAddr);
			m_client = accept(m_server, (SOCKADDR*)&m_clientAddr, &addrLength);
			if (m_client == INVALID_SOCKET)
			{
				break;
			}

			std::cout << "Connection Success!" << std::endl;
			//connection success
			while (1)
			{
				int ret = recv(m_client, m_buffer, sizeof(m_buffer), 0);
				if (ret == SOCKET_ERROR || ret == 0)
				{
					break;
				}
				std::cout << "Server Message : " << m_buffer << std::endl;
				Sleep(1000);
			}
			return ERROR_SERVER;
		}
	}
	return 0;
}
