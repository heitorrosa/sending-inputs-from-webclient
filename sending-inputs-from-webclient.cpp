#include <thread>
#include <iostream>
#include <winsock2.h>
#include <ws2tcpip.h>

using namespace std;

int websocket() {
    // Starts Winsock /// Create a WebSocket server socket
    WSADATA wsaData;
    WSAStartup(MAKEWORD(2, 2), &wsaData);

    SOCKET sock = socket(AF_INET, SOCK_STREAM, 0);
    if (sock == INVALID_SOCKET) {
        return 1;
    }

    // Bind the socket to a port /// Listen for incoming connections
    sockaddr_in addr;
    addr.sin_family = AF_INET;
    addr.sin_port = htons(80);
    addr.sin_addr.s_addr = INADDR_ANY;

    bind(sock, (sockaddr*)&addr, sizeof(addr));

    listen(sock, SOMAXCONN);

    // Connect to the server ///// Convert the IP address to a binary format | Create a sockaddr_in structure
    in_addr addr1;
    if (inet_pton(AF_INET, "wss://heitorrosa.github.io/sending-inputs-from-webclient", &addr1) != 0) {
        // Handle error
    }
    sockaddr_in addr_in;
    addr_in.sin_family = AF_INET;
    addr_in.sin_port = htons(80); // Default port for HTTPS
    addr_in.sin_addr = addr1;

    int connect_result = connect(sock, (sockaddr*)&addr_in, sizeof(addr_in));
    if (connect_result != 0) {
        // Handle error
    }

    // Keep the application running until you manually close it
    while (true) {
        // Accept an incoming connection
        SOCKET client_sock = accept(sock, NULL, NULL);
        if (client_sock == INVALID_SOCKET) {
            // Handle error
            continue;
        }

        // Send a message to the client
        const char* message = "localhost";
        int bytes_sent = send(client_sock, message, strlen(message), 0);
        if (bytes_sent != strlen(message)) {
            // Handle error
            closesocket(client_sock);
            continue;
        }

        // Receive data from the client
        char buffer[1024];
        int bytes_received = recv(client_sock, buffer, sizeof(buffer), 0);
        if (bytes_received == 0) {
            // Handle ping request
            // Close the client connection
            closesocket(client_sock);
            continue;
        }
        else if (bytes_received <= 0) {
            // Handle error
            closesocket(client_sock);
            continue;
        }

        // Process the data received from the client

        // Close the client connection
        closesocket(client_sock);
    }

    return 0;
}

int main() {
    websocket();

    return 0;
}
