#include <thread>
#include <iostream>
#include <winsock2.h>
#include <ws2tcpip.h>

using namespace std;

int websocket() {
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

    // Listen for incoming connections & accepts it
    listen(sock, SOMAXCONN);

    SOCKET client_sock = accept(sock, NULL, NULL);
    if (client_sock == INVALID_SOCKET) {
        return 1;
    }

    // Close the server socket
    closesocket(sock);

    // Send a message to the client
    const char* message = "localhost";
    send(client_sock, message, strlen(message), 0);

    // Receive a message from the client
    char buffer[1024];
    int bytes_received = recv(client_sock, buffer, sizeof(buffer), 0);

    // Close the client socket
    closesocket(client_sock);

    WSACleanup();

    return 0;
}

int main() {
    websocket();

    return 0;
}
 