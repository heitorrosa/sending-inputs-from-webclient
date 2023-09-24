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

	// Convert the IP address to a binary format
	in_addr addr1;
	if (inet_pton(AF_INET, "ws://heitorrosa.github.io/sending-inputs-from-webclient", &addr1) != 1) {
	}

	// Connect to the server
	sockaddr_in addr_in;
	addr_in.sin_family = AF_INET;
	addr_in.sin_port = htons(80); // Default port for HTTP
	addr_in.sin_addr = addr1;

	if (connect(sock, (sockaddr*)&addr_in, sizeof(addr_in)) == SOCKET_ERROR) {
		return 1;
	}

	// Send a request to the server
	char request[] = "GET / HTTP/1.1\r\nHost: ws://heitorrosa.github.io/sending-inputs-from-webclient\r\n\r\n";
	send(sock, request, sizeof(request), 0);

	// Close the socket
	closesocket(sock);

	return 0;
}

int main() {
	websocket();

	return 0;
}