#pragma comment(lib, "ws2_32.lib")
#include <stdio.h>
#define _WINSOCK_DEPRECATED_NO_WARNINGS
#include <winsock2.h>

int main(int argc, char **argv) {
	if (argc != 3) {
		printf("Usage %s server name as IP port number\n", argv[0]);
		return 1;
	}
	// Initialize Winsock. Please do it yourself!
	WSADATA wsa;
	int ret = WSAStartup((WORD)0x20002, &wsa);
	if (ret != 0) {
		printf("Winsock API failed to start\n");
		return 1;
	}
	SOCKET s;	 // Create a socket.
	s = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (s == INVALID_SOCKET) {
		printf("Client: socket() - Error at socket(): %ld\n", WSAGetLastError());
		WSACleanup(); return 0;
	}
	else printf("Client: socket() is OK.\n");

	sockaddr_in addr_connect;				//construct remote address
	addr_connect.sin_family = AF_INET;
	addr_connect.sin_addr.s_addr = inet_addr(argv[1]);
	addr_connect.sin_port = htons(atoi(argv[2]));
	// Connect to a server.
	if (connect(s, (SOCKADDR*)&addr_connect, sizeof(addr_connect)) == SOCKET_ERROR) {
		printf("Client: connect() - Failed to connect.\n"); WSACleanup(); return 0;
	}
	printf("Connect to sevrer\n");

	// Send and receive data.

	int bytesSent, bytesRecv = SOCKET_ERROR;
	char sb[200], rb[200] = "";
	while (strcmp(rb, "quit") != 0) {	//interactions with server
		printf("Client >");				//ask user to enter
		fgets(sb, sizeof(sb), stdin);	//get a sentence
		bytesSent = send(s, sb, strlen(sb), 0); //send mess to server
		printf("Client: send() - Bytes Sent: %ld\n", bytesSent);
		while (bytesRecv == SOCKET_ERROR) {
			bytesRecv = recv(s, rb, 200, 0);
			rb[bytesRecv] = '\0';
			if (bytesRecv == 0 || bytesRecv == WSAECONNRESET) {
				printf("Client: Connection Closed.\n"); break;
			}
			else printf("Client: recv() is OK. %d bytes received\n", bytesRecv);

			if (bytesRecv < 0) return 0;
			//else printf("Client: Bytes received - %ld.\n", bytesRecv);
		}	// close socket, please do it yourself.
	}	//end of while
	closesocket(s);
	printf("Closing communication\n");
	system("pause");
	WSACleanup();
	return 0;
}
