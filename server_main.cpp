#include "server.hpp"

int main() 
{
    try 
    {
        Server server(1604);
        server.run();
    } catch (const std::exception& e) 
    {
        std::cerr << "Error: " << e.what() << std::endl;
        return 1;
    }
    return 0;
}