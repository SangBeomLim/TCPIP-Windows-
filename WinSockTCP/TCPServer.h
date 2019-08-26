#ifndef TCPSERVER_H
#define TCPSERVER_H

//winsock
#pragma comment (lib, "ws2_32")
#include <WinSock2.h>
//C++ include
#include <iostream>
#include <string>
#include <thread>
//C include
#include <stdio.h>
#include <stdlib.h>


//define
#define HOST "127.0.0.1" 
#define PORT 9200
#define ERROR_SERVER -1
#define SUCCESS_SERVER 1


class TCPServer {

private:
	WSADATA m_wsa;
	SOCKET m_server, m_client;
	SOCKADDR_IN m_serverAddr, m_clientAddr;
	char m_buffer[1024];
protected:
public:
	bool m_ServerState;
private:
	int onInitialize();

protected:
public:
	TCPServer();
	virtual ~TCPServer();
	int onCommunication();
};
#endif