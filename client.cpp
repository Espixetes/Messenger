#include "client.hpp"


Client::Client(const std::string& ip, int port_num) 
    : sock_fd(-1), server_ip(ip), port(port_num) 
{
    initialize_socket();
}


Client::~Client() 
{
    if (sock_fd != -1) 
    {
        close(sock_fd);
    }
}

void Client::initialize_socket() 
{
    sock_fd = socket(AF_INET, SOCK_STREAM, 0);
    if (sock_fd < 0) 
    {
        throw std::runtime_error("Socket creation failed");
    }

    sockaddr_in server_addr{};
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(port);
    if (inet_pton(AF_INET, server_ip.c_str(), &server_addr.sin_addr) <= 0) 
    {
        close(sock_fd);
        throw std::runtime_error("Invalid address");
    }

    if (connect(sock_fd, (sockaddr*)&server_addr, sizeof(server_addr)) < 0) 
    {
        close(sock_fd);
        throw std::runtime_error("Connection failed");
    }
}

void Client::run() 
{
    std::cout << "Connected to server. Type messages (type 'disconnect' to exit):\n";
    
    char buffer[BUFFER_SIZE];
    std::string input;

    while (true) 
    {
        std::getline(std::cin, input);
        if (send(sock_fd, input.c_str(), input.length(), 0) < 0) 
        {
            throw std::runtime_error("Send failed");
        }

        if (input == "disconnect") 
        {
            break;
        }

        memset(buffer, 0, BUFFER_SIZE);
        int bytes = recv(sock_fd, buffer, BUFFER_SIZE - 1, 0);
        if (bytes <= 0) 
        {
            throw std::runtime_error("Server disconnected or error occurred");
        }

        buffer[bytes] = '\0';
        std::cout << "Server: " << buffer << std::endl;
    }
}
