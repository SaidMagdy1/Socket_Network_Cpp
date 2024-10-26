#include <iostream>
#include <string>
#include <algorithm>
#include <cstring>    // For memset
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>   // For close()
//states
#define DONE 0

int main(){

    int server_fd ,new_socket;
    int binding;
    int listening;
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

   // std::cout<<"first : "<<setsockopt(server_st, SOL_SOCKET, SO_REUSEADDR, &opt,sizeof(opt))<<std::endl;
    if(setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR, &opt,sizeof(opt)))
    {
        std::cerr << "setsockopt failed" << std::endl;
        return -1;
    }

    address.sin_family=AF_INET;   //IPv4
    address.sin_addr.s_addr=INADDR_ANY;  // that is mean any address
    address.sin_port = htons(port); //htons keeps the port big enddian  i think the opposite is ntohs()
      /* ( Big-endian is an order in which the big end -- the most significant value in the sequence -- is first, 
    at the lowest storage address. 
    Little-endian is an order in which the little end,
    the least significant value in the sequence, is first.)*/


    binding=bind(server_fd , (struct sockaddr *)&address ,sizeof(address));
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


    new_socket = accept(server_fd, (struct sockaddr *)&address, (socklen_t*)&addrlen);
    if(new_socket < DONE)
    {
        std::cerr << "Accept failed" << std::endl;
        return -1;
    }

    //sending messages
  
    std::string message;
    while (true) {
        // Receive message from client
        memset(buffer, 0, sizeof(buffer)); // Clear buffer
        int bytes_received = recv(new_socket, buffer, sizeof(buffer), 0);
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
        send(new_socket, message.c_str(), message.length(), 0);
        std::cout << "Message sent: " << message << std::endl;
    }

    std::cout << "Server closing..." << std::endl;
    close(new_socket);
    close(server_fd);
    

    return 0;
}