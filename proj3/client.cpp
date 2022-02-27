// client.cpp
// Tyler Chase
// Solomon Himelbloom
// 2022-02-26
//
// For CS 321 Spring 2022
// Lab 3: Server & Client Programming

#include <stdio.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <string>
#include <iostream>
#define PORT 42069

int main(int argc, char const *argv[])
{
    int sock = 0;
    struct sockaddr_in serv_addr;

    if ((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0)
    {
        std::cout << "Socket creation error :: cerr" << std::endl;
        return -1;
    }

    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(PORT);

    // Convert IPv4 and IPv6 addresses from text to binary form
    if (inet_pton(AF_INET, "127.0.0.1", &serv_addr.sin_addr) <= 0)
    {
        std::cout << "Invalid address -- address not supported :: cerr" << std::endl;
        return -1;
    }

    if (connect(sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0)
    {
        std::cout << "Connection Failed :: cerr" << std::endl;
        return -1;
    }
    while (true)
    {
        std::cout << "Type a message to send: ";
        std::string sentMessage;
        std::getline(std::cin,sentMessage);

        char integer[4];
        *((int *)integer) = sentMessage.length();
        send(sock, integer, sizeof(int), 0);
        send(sock, sentMessage.c_str(), sentMessage.length(), 0);
        std::cout << "Message sent" << std::endl;
        // recieve message back
        int messageLength;
        read(sock, &messageLength, sizeof(int));
        std::string recievedMessage;
        recievedMessage.resize(messageLength);
        read(sock, &recievedMessage[0], messageLength);
        std::cout << "Message recived from server: " << recievedMessage.c_str() << std::endl;
        if (!recievedMessage.compare("BYE"))
        {
            std::cout << "Client has disconnected." << std::endl;
            return 0;
        }
    }

    return 0;
}
