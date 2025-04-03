#include <iostream>
#include <string>
#include <algorithm>
#include <cstring>    // For memset
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h> // For sockaddr_in
#include <unistd.h>    // For close()
#include <arpa/inet.h> // For inet_addr("127.0.0.1");  
//states
#define DONE 0

int main(){

    int server_fd ,client_sock;
    int binding;
    int listening;
    struct sockaddr_in hint;
    struct sockaddr_in address;
    int addrlen=sizeof(address);
    int opt = 1;
    int port=5555;
    char buffer[1024] = {0};

    //Socket Initialization (File descriptor) 
    server_fd = socket(AF_INET,SOCK_STREAM,0);
    //std::cout<<"first : "<<server_st<<std::endl;
    if(server_fd == DONE)
    {
        std::cerr<<"Can Not Init the Socket"<<std::endl;
        return -1;
    }

    hint.sin_family=AF_INET;   //IPv4
    hint.sin_addr.s_addr=inet_addr("127.0.0.1");  
    hint.sin_port = htons(port); //htons keeps the port big enddian  i think the opposite is ntohs()
      /* ( Big-endian is an order in which the big end -- the most significant value in the sequence -- is first, 
    at the lowest storage address. 
    Little-endian is an order in which the little end,
    the least significant value in the sequence, is first.)*/


    binding=bind(server_fd , (struct sockaddr *)&hint ,sizeof(hint));
    //std::cout<<"binding : "<<binding<<std::endl;
    if(binding < DONE)
    {
         std::cerr << "Binding failed" << std::endl;
        return -1;
    }


    listening=listen(server_fd , 5);
    //std::cout<<"listening : "<<listening<<std::endl;
    if(listening < DONE)
    {
        std::cerr << "Listen failed" << std::endl;
        return -1;
    }
  
    std::cout << "Server listening on port " << port << std::endl;


    client_sock = accept(server_fd, (struct sockaddr *)&address, (socklen_t*)&addrlen);
    if(client_sock < DONE)
    {
        std::cerr << "Accept failed" << std::endl;
        return -1;
    }

  
    std::string message;
    while (true) {
        // Receive message from client
        memset(buffer, 0, sizeof(buffer)); // Clear buffer
        int bytes_received = recv(client_sock, buffer, sizeof(buffer), 0);
        if (bytes_received > 0) {
            std::cout << "Message from client: " << buffer << std::endl;
        }

        // Prompt server user to enter a message to send
        std::cout << "Enter message to send to client (type 'exit' to close): ";
        std::getline(std::cin, message);

        // Exit loop if user types "exit"
        if (message == "exit") {
            break;
        }

        // Send the message to the client
        send(client_sock, message.c_str(), message.length(), 0);
        std::cout << "Message sent: " << message << std::endl;
    }

    std::cout << "Server closing..." << std::endl;
    close(client_sock);
    close(server_fd);
    

    return 0;
}