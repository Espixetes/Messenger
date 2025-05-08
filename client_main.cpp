#include "client.hpp"

int main() 
{
    try 
    {
        Client client("127.0.0.1", 1604);
        client.run();
    } catch (const std::exception& e) 
    {
        std::cerr << "Error: " << e.what() << std::endl;
        return 1;
    }
    return 0;
}