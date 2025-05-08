#include <string>
#include <iostream>
#include <cstring>
#include <unistd.h>
#include <arpa/inet.h>
#include <stdexcept>

class Client 
{
private:
    static constexpr size_t BUFFER_SIZE = 1024;
    int sock_fd;
    std::string server_ip;
    int port;

    void initialize_socket();

public:
    Client(const std::string& ip, int port_num);
    ~Client();

    void run();
};