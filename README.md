# Client-Server Application



## Files
- `client_main.cpp`: Main file for the client application.
- `client.cpp`: Client implementation logic.
- `client.hpp`: Header file for the client.
- `server_main.cpp`: Main file for the server application.
- `server.cpp`: Server implementation logic.
- `server.hpp`: Header file for the server.
- `Makefile`: Build script to compile the project.

## How a Basic Client-Server System Works
- If the client sends **hello** message, the server should respond **world**.
- If any other message is sent, the server should send it back to the client without changing it.
- If the client sends **disconnect** message, exchange messages will end.
