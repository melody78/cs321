// server.cpp
// Tyler Chase
// Solomon Himelbloom
// 2022-02-26
//
// For CS 321 Spring 2022
// Lab 3: Server & Client Programming

#include <arpa/inet.h>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <ctime>
#include <iostream>
#include <errno.h>
#include <netinet/in.h>
#include <stdlib.h>
#include <string>
#include <sys/socket.h>
#include <sys/types.h>
#include <sys/time.h>
#include <unistd.h>
#include <vector>

#define LOCALHOST "127.0.0.1"
#define PORT 8000

int main(int argc, char const *argv[])
{
    int server_fd, master_socket;
    std::vector<int> sockets{0, 0};
    struct sockaddr_in address;
    int option = 1;
    fd_set readfds;

    // Creating socket file descriptor create an endpoint for communication.
    // Basically opens a file where both the communicating parties can write.
    // [stdlib.h] EXIT_SUCCESS = 0 & EXIT_FAILURE = 8
    if ((master_socket = socket(AF_INET, SOCK_STREAM, 0)) == 0)
    {
        std::cerr << "Socket failed." << std::endl;
        exit(EXIT_FAILURE);
    }

    // Forcefully attaching socket to the port 8000 set the socket options.
    // https://pubs.opengroup.org/onlinepubs/000095399/functions/setsockopt.html
    if (setsockopt(master_socket, SOL_SOCKET, SO_REUSEADDR, (char *)&option, sizeof(option)) < 0)
    {
        std::cerr << "[setsockopt]" << std::endl;
        exit(EXIT_FAILURE);
    }

    // AF_INET specifies the address family (IPv4).
    // INADDR_ANY is an IP address that is used for an unspecified IP address.
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(PORT);

    // Forcefully attaching socket to the port 8000.
    // Bind the socket file descriptor to the socket address.
    // Online resource: https://pubs.opengroup.org/onlinepubs/009695399/functions/bind.html
    if (bind(master_socket, (struct sockaddr *)&address, sizeof(address)) < 0)
    {
        std::cerr << "Bind failed!" << std::endl;
        exit(EXIT_FAILURE);
    }

    // Listen for connections on a socket.
    if (listen(master_socket, 3) < 0)
    {
        std::cerr << "Listening..." << std::endl;
        exit(EXIT_FAILURE);
    }

    int address_length = sizeof(address);

    while (true)
    {
        FD_ZERO(&readfds);

        FD_SET(master_socket, &readfds);
        int max_sd = master_socket;
        for (int socket : sockets)
        {
            if (socket > 0)
            {
                FD_SET(socket, &readfds);
            }
            if (socket > max_sd)
            {
                max_sd = socket;
            }
        }
        int activity = select(max_sd + 1, &readfds, NULL, NULL, NULL);
        std::cout << ("(!) ACTIVITY HAS BEEN DETECTED") << std::endl;
        if (FD_ISSET(master_socket, &readfds))
        {
            std::cout << "A new user has joined the server!" << std::endl;
            // Take on new connections and add them to the list of sockets.
            int new_socket;
            new_socket = accept(master_socket, (struct sockaddr *)&address, (socklen_t *)&address_length);
            sockets.push_back(new_socket);
        }
        else
        {  
            std::cout << "Test" << std::endl;
            int message_length;
            int valread;
            for (int &sd : sockets)
            {
                if (FD_ISSET(sd, &readfds))
                {
                    if ((valread = read(sd, &message_length, sizeof(int))) == 0)
                    {
                        getpeername(sd, (struct sockaddr *)&address,
                                    (socklen_t *)&address_length);

                        printf("Host disconnected. | IP: %s | PORT: %d \n",
                               inet_ntoa(address.sin_addr), ntohs(address.sin_port));

                        close(sd);
                        sd = 0;
                        std::cout << ("LEAVING?") << std::endl;
                    }
                    else
                    {

                        std::string delivery;
                        delivery.resize(message_length);
                        read(sd, &delivery[0], message_length);
                        std::cout << "🆕 Received delivery: " << delivery << std::endl;

                        // send a message to all client that are not the user that sent stuff
                        for (int &sda : sockets)
                        {
                            if (sda != 0 && sda != sd)
                            {
                                send(sda, &message_length, sizeof(int), 0);
                                send(sda, delivery.c_str(), delivery.length(), 0);
                            }
                        }

                        if (!delivery.compare("BYE"))
                        {
                            std::cout << "Server has disconnected." << std::endl;
                            return 0;
                        }
                        std::cout << ("WHY") << std::endl;
                    }
                }
            }
        }
    }
}
