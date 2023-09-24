#include <thread>
#include <iostream>
#include <winsock2.h>
#include <ws2tcpip.h>

using namespace std;

int websocket()
{
	// Starts Winsock
	WSADATA wsaData;
	WSAStartup(MAKEWORD(2, 2), &wsaData);

	// Create a WebSocket server socket
	SOCKET sock = socket(AF_INET, SOCK_STREAM, 0);
	if (sock == INVALID_SOCKET) {
		return 1;
	}

	// Bind the socket to a port
	sockaddr_in addr;
	addr.sin_family = AF_INET;
	addr.sin_port = htons(80);
	addr.sin_addr.s_addr = INADDR_ANY;

	bind(sock, (sockaddr*)&addr, sizeof(addr));

	// Listen for incoming connections
	listen(sock, SOMAXCONN);

	// Start the WebSocket server loop
	while (true) {
		// Accept incoming connections
		SOCKET client_sock = accept(sock, NULL, NULL);
		if (client_sock == INVALID_SOCKET) {
			break;
		}
	}

	// Close the socket
	closesocket(sock);

	return 0;
}

int main() {
	websocket();

	return 0;
}