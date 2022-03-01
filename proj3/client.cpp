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
#include <ostream>
#define PORT 8000

int main(int argc, char const *argv[])
{
    int sock = 0;
    struct sockaddr_in serv_addr;

    if ((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0)
    {
        std::cout << "(!) Socket creation error." << std::endl;
        return -1;
    }

    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(PORT);

    // Convert IPv4 and IPv6 addresses from text to binary form
    if (inet_pton(AF_INET, "127.0.0.1", &serv_addr.sin_addr) <= 0)
    {
        std::cerr << "(!) Invalid address -- current address not supported." << std::endl;
        return -1;
    }

    if (connect(sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0)
    {
        std::cerr << "🚫 Connection failed!" << std::endl;
        return -1;
    }
    while (true)
    {
        std::cerr << ">> Type a message to send: ";
        std::string sent_message;
        std::getline(std::cin, sent_message);

        char integer[4];
        *((int *)integer) = sent_message.length();
        send(sock, integer, sizeof(int), 0);
        send(sock, sent_message.c_str(), sent_message.length(), 0);
        std::cout << "✅ Message sent." << std::endl;

        // Recieve the corresponding message back.
        int message_length;

        read(sock, &message_length, sizeof(int));
        std::string recieved_message;
        recieved_message.resize(message_length);
        read(sock, &recieved_message[0], message_length);
        std::cout << "Message recived from server: " << recieved_message.c_str() << std::endl;

        if (!recieved_message.compare("BYE") || !recieved_message.compare("bye"))
        {
            std::cout << "Client has disconnected." << std::endl;
            return 0;
        }
    }

    return 0;
}
