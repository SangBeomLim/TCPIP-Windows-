// WinSockTCP.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "TCPClient.h"
#include "TCPServer.h"
#include <thread>
#include <Windows.h>

using namespace std;
thread thd[2]; //loop thread 2 alloc
TCPServer serv;
TCPClient client;
void server_thread(int tid);
void client_thread(int tid);

int main()
{

	cout << "Main Function Start" << endl;

	thd[0] = thread(server_thread, 0);
	thd[0].join();

    return 0;
}

void server_thread(int tid)
{
	cout << "server_thread_start!!" << endl;
	thd[1] = thread(client_thread, 1);
	serv.onCommunication();
	thd[1].join();
}

void client_thread(int tid)
{
	cout << "client_thread_start!!" << endl;

	client.onCommunication();


}