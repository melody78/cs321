// server.cpp
// Tyler Chase
// Solomon Himelbloom
// 2022-02-26
//
// For CS 321 Spring 2022
// Lab 3: Server & Client Programming

#include <unistd.h>
#include <stdio.h>
#include <sys/socket.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <string.h>
#include <string>
#include <iostream>
#define PORT 8000

int main(int argc, char const *argv[]) {
    int server_fd, new_socket;
    struct sockaddr_in address; // Structures for handling internet addresses
    int opt = 1;
    int addrlen = sizeof(address);

    // Creating socket file descriptor create an endpoint for communication. 
    // Basically opens a file where both the communicating parties can write.
    // [stdlib.h] EXIT_SUCCESS = 0 & EXIT_FAILURE = 8
    if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0)
    {
        perror("socket failed");
        exit(EXIT_FAILURE);
    }

    // Forcefully attaching socket to the port 8000 set the socket options.
    // https://pubs.opengroup.org/onlinepubs/000095399/functions/setsockopt.html
    if (setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt)))
    {
        perror("setsockopt");
        exit(EXIT_FAILURE);
    }

    // AF_INET specisies what family of address it is (here it is IPv4).
    // INADDR_ANY is an IP address that is used for an unspecified IP address.
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(PORT);

    // Forcefully attaching socket to the port 8000.
    // Bind the socket file descriptor to the socket address.
    // Online resource: https://pubs.opengroup.org/onlinepubs/009695399/functions/bind.html
    if (bind(server_fd, (struct sockaddr *)&address, sizeof(address)) < 0)
    {
        perror("bind failed");
        exit(EXIT_FAILURE);
    }

    // Listen for connections on a socket.
    if (listen(server_fd, 3) < 0)
    {
        perror("listen");
        exit(EXIT_FAILURE);
    }

    if ((new_socket = accept(server_fd, (struct sockaddr *)&address, (socklen_t *)&addrlen)) < 0)
    {
        perror("accept");
        exit(EXIT_FAILURE);
    }

    while (true)
    {
        int message_length;

        read(new_socket, &message_length, sizeof(int));
        std::string message;
        message.resize(message_length);
        read(new_socket, &message[0], message_length);
        std::cout << "Recieved message: " << message << std::endl;

        char integer[4];
        *((int *)integer) = message.length();
        send(new_socket, integer, sizeof(int), 0);
        send(new_socket, message.c_str(), message.length(), 0);

        if (!message.compare("BYE") || !message.compare("bye"))
        {
            std::cout << "Server has disconnected." << std::endl;
            return 0;
        }
    }

    return 0;
}
