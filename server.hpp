#include <string>
#include <thread>
#include <iostream>
#include <cstring>
#include <unistd.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <stdexcept>

class Server
{
private:
    static constexpr size_t BUFFER_SIZE = 1024;
    int server_fd;
    int port;

    void initialize_socket();
    static void handle_client(int client_socket);

public:
    Server(int port_num);
    ~Server();

    void run();
};