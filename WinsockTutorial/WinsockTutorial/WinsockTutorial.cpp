// WinsockTutorial.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <winsock2.h>
#include <iostream>
#pragma comment(lib,"WS2_32")

#define NETWORK_ERROR -1
#define NETWORK_OK 0
#define PORT 8765

void reportError(int, const char *);

int main()
{
	WORD sockVersion;
	WSADATA wsaData;
	int nret;

	sockVersion = MAKEWORD(1, 1);  //generates winsock version 1.1
	WSAStartup(sockVersion, &wsaData);  //we initiallize the winsock here
	

	SOCKET listeningSocket;

	listeningSocket = socket(AF_INET,		//send messages over TCP/IP
		SOCK_STREAM,						//stream-oriented socket
		IPPROTO_TCP);						//use TCP rather than UDP

	if (listeningSocket == INVALID_SOCKET)
	{
		nret = WSAGetLastError();			//getting the int error code returned from faulty socket init
		reportError(nret, "socket()");		//telling our function what failed

		WSACleanup();						//shutdown winsock
		return NETWORK_ERROR;
	}

	//fill in address info
	SOCKADDR_IN serverInfo;
	serverInfo.sin_family = AF_INET;				
	serverInfo.sin_addr.s_addr = INADDR_ANY;		//socket is listening for connections, so any address will work
	serverInfo.sin_port = htons(PORT);				//convert 8888 into a 'network-byte order' and insert it into the port field


	//bind the socket to our local server address
	nret = bind(listeningSocket, (LPSOCKADDR)&serverInfo, sizeof(serverInfo));

	if (nret == SOCKET_ERROR)
	{
		nret = WSAGetLastError();
		reportError(nret, "bind()");

		WSACleanup();
		return NETWORK_ERROR;
	}

	//make the socket listen
	nret = listen(listeningSocket, 10);			//allows 10 connections to wait for connection

	if (nret == SOCKET_ERROR)
	{
		nret = WSAGetLastError();
		reportError(nret, "listen()");

		WSACleanup();
		return NETWORK_ERROR;
	}


	//wait for a client
	SOCKET theClient;

	theClient = accept(listeningSocket, NULL, NULL);

	if (theClient == INVALID_SOCKET)
	{
		nret = WSAGetLastError();
		reportError(nret, "accept()");

		WSACleanup();
		return NETWORK_ERROR;
	}

	
	//send messages and what not
	//send()


	closesocket(theClient);
	closesocket(listeningSocket);
	WSACleanup();
	return NETWORK_OK;

}


void reportError(int errorCode, const char *whichFunc)
{
	char errorBuff[92];

	ZeroMemory(errorBuff, 92);     //clears 92 units of memory starting at the location of errorBuff

	sprintf(errorBuff, "Call to %s returned error %d!", (char *)whichFunc, errorCode);  //stores error in errorBuff

	WCHAR errorMessage[92];
	for (int i = 0; i < 92; i++)						//converting regular chars to wide chars so they can be output using messagebox which uses unicode
		errorMessage[i] = WCHAR(errorBuff[i]);

	MessageBox(NULL, LPCWSTR(errorMessage), L"SocketIndicationError", MB_OK);  //creates a WINAPI message box to display errorBuff as a 'Long Pointer to Constant Wide String'(stores characters in 2-byte chars)

}
