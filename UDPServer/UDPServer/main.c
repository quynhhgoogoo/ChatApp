#pragma comment(lib, "ws2_32.lib")
#include <WinSock2.h>
#include <stdio.h>

int main(void) {
	WSADATA wsa;
	SOCKET s;		//create a socket instance
	int re = WSAStartup(MAKEWORD(2,2), &wsa);	//start the Winsock

	if (re != 0) {
		printf("WSA cannot start\n");
		return 1;
	}
	printf("Welcome to Winsock API\n");
	s = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);		//create a socket
	if (s == INVALID_SOCKET) {
		printf("Socket cannot be created\n");
		return 1;
	}
	printf("Socket is created\n");
	SOCKADDR_IN saddr;						//address instance for server
	saddr.sin_family = AF_INET;				//IPv4
	saddr.sin_addr.s_addr = INADDR_ANY;		//take any allocated address from host
	saddr.sin_port = htons(55555);

	if (bind(s, (SOCKADDR_IN*)&saddr, sizeof(saddr)) == SOCKET_ERROR) {
		printf("Bind is failed");
		closesocket(s);
		return 1;
	}
	printf("Port %d is openned for incomming UDP diagrams\n", 55555);
	system("pause");	//halt for user to press a key
	closesocket(s);
	WSACleanup();
	system("pause");	//halt for user to press a key
}