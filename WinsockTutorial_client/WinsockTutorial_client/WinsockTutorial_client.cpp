// WinsockTutorial_client.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <winsock2.h>
#include <iostream>
#include <cstdlib>
#pragma comment(lib,"WS2_32")
using std::cout;
using std::cin;
using std::endl;

#define NETWORK_ERROR -1
#define NETWORK_OK 0
#define PORT 8765

void reportError(int errorCode, const char *whichFunc);

int main()
{
	WORD sockVersion;
	WSADATA wsaData;
	int nret;

	sockVersion = MAKEWORD(1, 1);  
	WSAStartup(sockVersion, &wsaData);

	//get that HOSTENT son
	LPHOSTENT hostEntry;
	char shastaHostName[255];
	gethostname(shastaHostName, 255);
	hostEntry = gethostbyname(shastaHostName);

	if (!hostEntry)
	{
		nret = WSAGetLastError();
		reportError(nret, "gethostbyaddr()");

		WSACleanup();
		return NETWORK_ERROR;
	}

	//Make the socket that will become our client
	SOCKET theSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);

	if (theSocket == INVALID_SOCKET)
	{
		nret = WSAGetLastError();			
		reportError(nret, "socket()");		

		WSACleanup();						
		return NETWORK_ERROR;
	}

	//prepare for connection by filling sockaddr struct with info about the server
	SOCKADDR_IN serverInfo;
	serverInfo.sin_family = AF_INET;
	serverInfo.sin_addr = *((LPIN_ADDR)*hostEntry->h_addr_list);
	serverInfo.sin_port = htons(PORT);

	//connect to server!
	nret = connect(theSocket, (LPSOCKADDR)&serverInfo, sizeof(serverInfo));

	if (nret == SOCKET_ERROR)
	{
		nret = WSAGetLastError();
		reportError(nret, "connect()");

		WSACleanup();
		return NETWORK_ERROR;
	}

	//recieve messages and what not
	char dataBuff[256];
	while (nret != SOCKET_ERROR)
	{
		nret = recv(theSocket, dataBuff, 5 + 1, 0);
		if (nret == SOCKET_ERROR)
		{
			nret = WSAGetLastError();
			reportError(nret, "recv()");

			closesocket(theSocket);
			WSACleanup();
			return NETWORK_ERROR;
		}
		//error check in case the server is sending wonky packets
		if (nret != (5 + 1))
		{
			closesocket(theSocket);
			WSACleanup();
			return NETWORK_ERROR;
		}
		cout << "Data Packet: ";
		for (int i = 0; i < strlen(dataBuff); i++)
		{
			cout << (unsigned int)(unsigned char)dataBuff[i] << " ";
		}
		cout << endl;
	}

	closesocket(theSocket);
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