#pragma comment(lib, "ws2_32.lib")
#include <stdio.h>
#include <winsock2.h>

int main(int argc, char **argv) {
	if (argc != 2) {
		printf("Usage: %s port number\n", argv[0]);
		return 1;
	}

	// Initialize Winsock. Please do it yourself!
	WSADATA wsa;
	int ret = WSAStartup((WORD)0x20002, &wsa);
	if (ret != 0) {
		printf("Winsock API can not start up\n");
		return 1;
	}

	// make a socket to listen for incoming connection requests.
	SOCKET ls;
	ls = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	// check if the socket is created correctly: e.g.: if…else printf("Server: socket() is OK.\n");
	if (ls == INVALID_SOCKET) {
		printf("cannot create a socket\n");
		return 1;
	}
	// setup sockaddr_in structure for IP address and port for the socket that is being bound.
	sockaddr_in addr_lis;
	addr_lis.sin_family = AF_INET; addr_lis.sin_addr.s_addr = htonl(INADDR_ANY);  //inet_addr("127.0.0.1");
	addr_lis.sin_port = htons(atoi(argv[1]));

	if (bind(ls, (SOCKADDR*)&addr_lis, sizeof(addr_lis)) == SOCKET_ERROR) {
		printf("Server: bind() failed.\n"); closesocket(ls);
		return 0;
	}	// if binding is OK
	else printf("Server: bind() is OK.\n");

	// Listen for incoming connection requests on the created socket
	if (listen(ls, 10) == SOCKET_ERROR) printf("Server: Error listening on socket.\n");
	else printf("Server: listen() is OK.\n");

	// Create a SOCKET for accepting incoming requests.
	SOCKET AcceptSocket;
	char recvbuf[256], sendbuf[256];
	printf("Server: Waiting for client to connect...\n");
	while (1) {		 // Accept the connection if any...
		AcceptSocket = SOCKET_ERROR;
		while (AcceptSocket == SOCKET_ERROR) AcceptSocket = accept(ls, NULL, NULL);
		printf("Server: accept() is OK.\n");
		printf("Server: Client connected...ready for communication.\n");
		while (strcmp(recvbuf, "quit") != 0) {
			//ls = AcceptSocket;
			int bytesRecv = recv(AcceptSocket, recvbuf, sizeof(recvbuf), 0);
			if (bytesRecv > 0) {
				recvbuf[bytesRecv] = '\0';		//add terminator for received string
				printf("Received %d bytes : %s", bytesRecv, recvbuf);
				printf("Server >");
				fgets(sendbuf, sizeof(sendbuf), stdin);
				int bytesSend = send(AcceptSocket, sendbuf, strlen(sendbuf), 0);
			}
		}
		break;
	}
	//close socket, please do it yourself
	closesocket(AcceptSocket);
	WSACleanup();
	return 0;
}
