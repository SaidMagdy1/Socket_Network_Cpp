#include <iostream>
#include <string>
#include <cstring>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#define DONE 0

int main() {
    int sock = 0;
    struct sockaddr_in serv_addr;
    const char *server_ip = "127.0.0.1"; // Server IP
    const int port = 5555;
    char buffer[1024] = {0};

    // Create socket
    if ((sock = socket(AF_INET, SOCK_STREAM, 0)) < DONE) {
        std::cerr << "Socket creation error" << std::endl;
        return -1;
    }

    serv_addr.sin_family = AF_INET; // IPv4
    serv_addr.sin_port = htons(port); // Port

    // Convert IPv4 and IPv6 addresses from text to binary form
    if (inet_pton(AF_INET, server_ip, &serv_addr.sin_addr) <= DONE) {
        std::cerr << "Invalid address / Address not supported" << std::endl;
        return -1;
    }

    // Connect to the server
    if (connect(sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < DONE) {
        std::cerr << "Connection failed" << std::endl;
        return -1;
    }

    // Read the message from server

    std::string message;
    while (true) {
        // Get user input to send to server
        std::cout << "Enter message to send to server (type 'exit' to close): ";
        std::getline(std::cin, message);

        // Exit loop if user types "exit"
        if (message == "exit") {
            break;
        }

        // Send the message to the server
        send(sock, message.c_str(), message.length(), 0);

        // Read message from server
        memset(buffer, 0, sizeof(buffer)); // Clear buffer
        recv(sock, buffer, sizeof(buffer), 0);
        std::cout << "Message from server: " << buffer << std::endl;
    }

    std::cout << "Client closing..." << std::endl;

    // read(sock, buffer, 1024);
    // std::cout << "Message from server: " << buffer << std::endl;

    close(sock);
    return 0;
}