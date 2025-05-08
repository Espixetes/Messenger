all: client server

client: client_main.cpp client.cpp
	g++ client_main.cpp client.cpp -o client

server: server_main.cpp server.cpp
	g++ server_main.cpp server.cpp -o server

clean:
	rm -f client server

