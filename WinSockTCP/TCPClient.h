#ifndef TCPCLIENT_H
#define TCPCLIENT_H

#pragma comment(lib, "ws2_32")
#include <WinSock2.h>
#include <WS2tcpip.h>
//include
#include <iostream>
#include <thread>
#include <string>
#include <stdio.h>
#include <stdlib.h>

//define
#define HOST "127.0.0.1"
#define PORT 9200
#define ERROR_CLIENT -1
#define SUCCESS_CLIENT 1
#define _WINSOCK_DEPRECATED_NO_WARNINGS

class TCPClient {
public:
	TCPClient();
	virtual ~TCPClient();
	int onCommunication();
protected:
private:
	int onInitialize();
public:
	bool m_ClientState;
protected:
private:
	WSADATA m_wsa;
	SOCKET m_client;
	SOCKADDR_IN m_serverAddr;
	char m_buffer[1024];
};
#endif // !TCPCLIENT_H

