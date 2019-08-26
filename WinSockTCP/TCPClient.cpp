#include "stdafx.h"
#include "TCPClient.h"

TCPClient::TCPClient()
{
	m_wsa = { 0 };
	m_serverAddr = { 0 };
	m_ClientState = false;
	memset(&m_buffer, 0x00, sizeof(m_buffer));
	m_ClientState = onInitialize();
}
TCPClient::~TCPClient()
{
	closesocket(m_client);
	WSACleanup();
}

int TCPClient::onInitialize()
{
	if (WSAStartup(MAKEWORD(2, 2), &m_wsa) != 0)
		return ERROR_CLIENT;

	m_client = socket(AF_INET, SOCK_STREAM, 0);
	if (m_client == INVALID_SOCKET)
		return ERROR_CLIENT;

	m_serverAddr.sin_family = AF_INET;
	m_serverAddr.sin_addr.s_addr = inet_addr(HOST);
	m_serverAddr.sin_port = htons(PORT);

	return SUCCESS_CLIENT;
}

int TCPClient::onCommunication()
{
	int ret = connect(m_client, (SOCKADDR*)&m_serverAddr, sizeof(m_serverAddr));
	if (ret == SOCKET_ERROR)
	{
		std::cout << "SOCKET_ERROR " << std::endl;
		return ERROR_CLIENT;
	}

	sprintf_s(m_buffer, "%s", "Hello TEST THREAD AND TCPIP\n");
	while (1)
	{
		printf("Client Message : %s", m_buffer);
		send(m_client, (char*)&m_buffer, sizeof(m_buffer), 0);
		Sleep(1000);
	}
	
	return 0;
}