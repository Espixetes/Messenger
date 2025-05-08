#include "server.hpp"


Server::Server(int port_num) : server_fd(-1), port(port_num) 
{
    initialize_socket();
}


Server::~Server() 
{
    if (server_fd != -1) 
    {
        close(server_fd);
    }
}

void Server::initialize_socket() 
{
    server_fd = socket(AF_INET, SOCK_STREAM, 0);
    if (server_fd < 0) 
    {
        throw std::runtime_error("Socket creation failed");
    }

    sockaddr_in server_addr{};
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(port);
    server_addr.sin_addr.s_addr = INADDR_ANY;

    if (bind(server_fd, (sockaddr*)&server_addr, sizeof(server_addr)) < 0) 
    {
        close(server_fd);
        throw std::runtime_error("Bind failed");
    }

    if (listen(server_fd, 5) < 0) 
    {
        close(server_fd);
        throw std::runtime_error("Listen failed");
    }
}

void Server::handle_client(int client_socket) 
{
    char buffer[BUFFER_SIZE];

    while (true) 
    {
        memset(buffer, 0, BUFFER_SIZE);
        int received = recv(client_socket, buffer, BUFFER_SIZE - 1, 0);
        if (received <= 0) 
        {
            break;
        }

        buffer[received] = '\0';
        std::string msg(buffer);
        msg.erase(msg.find_last_not_of(" \n\r\t") + 1); 

        if (msg == "disconnect") 
        {
            break;
        }

        std::string response = (msg == "hello") ? "world" : msg;
        if (send(client_socket, response.c_str(), response.length(), 0) < 0) 
        {
            break;
        }
    }

    close(client_socket);
    std::cout << "Client disconnected.\n";
}

void Server::run() 
{
    std::cout << "Server listening on port " << port << std::endl;

    while (true) 
    {
        sockaddr_in client_addr{};
        socklen_t client_len = sizeof(client_addr);
        int client_socket = accept(server_fd, (sockaddr*)&client_addr, &client_len);
        if (client_socket < 0) 
        {
            std::cerr << "Accept failed: " << strerror(errno) << std::endl;
            continue;
        }

        std::thread(handle_client, client_socket).detach();
    }
}

