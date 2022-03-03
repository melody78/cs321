// client.cpp
// Tyler Chase
// Solomon Himelbloom
// 2022-02-26
//
// For CS 321 Spring 2022
// Lab 3: Server & Client Programming

#include <cstdio>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <string>
#include <iostream>
#include <ostream>

#define LOCALHOST "127.0.0.1"
#define PORT 8000

int main(int argc, char const *argv[])
{
    int sock = 0;
    struct sockaddr_in server_address
    {
    };

    if ((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0)
    {
        std::cerr << "(!) Socket creation error." << std::endl;
        return -1;
    }

    server_address.sin_family = AF_INET;
    server_address.sin_port = htons(PORT);

    // Convert IPv4 and IPv6 addresses from text to binary form
    if (inet_pton(AF_INET, LOCALHOST, &server_address.sin_addr) <= 0)
    {
        std::cerr << "❌ Invalid address -- current address not supported." << std::endl;
        return -1;
    }

    if (connect(sock, (struct sockaddr *)&server_address, sizeof(server_address)) < 0)
    {
        std::cerr << "🚫 Connection failed!" << std::endl;
        return -1;
    }

    while (true)
    {
        std::string sent_message;
        std::cout << ">> Type a message to send: ";
        std::getline(std::cin, sent_message);

        char integer[4];
        *((int *)integer) = sent_message.length();
        // send(sock, integer, sizeof(int), 0);
        send(sock, sent_message.c_str(), sent_message.length(), 0);
        std::cout << "✅ Message sent." << std::endl;

        // Receive the corresponding message back.
        int message_length = 1024;

        // read(sock, &message_length, sizeof(int));
        std::string received_message;
        received_message.resize(message_length);
        read(sock, &received_message[0], message_length);
        std::cout << "Message received from server: " << received_message.c_str() << std::endl;

        if (!received_message.compare("BYE") || !received_message.compare("bye"))
        {
            std::cout << "Client has disconnected." << std::endl;
            return 0;
        }
    }
}
