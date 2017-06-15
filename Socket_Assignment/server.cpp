// Server

#define _WINSOCK_DEPRECATED_NO_WARNINGS
#include <winsock2.h>
#include <WS2tcpip.h>
#include <iostream>
#include <cstdio>
#include "server.h"
#pragma comment(lib,"ws2_32.lib")  // indicates to the linker that the ws2_32.lib (Winsock library) file is needed

int main() {
	int iResult;

	// Initialize WinSock 
	std::cout << "Initializing WinSock" << std::endl;
	WSADATA wsaData;                        // Create a WSADATA object containing info on Windows sockets implementation
	iResult = WSAStartup(MAKEWORD(2, 2), &wsaData);   // Initiate the use of WS2_32.dll 
	if (iResult != 0) {
		std::cout << "WSAStartup failed: " << iResult << std::endl;
		return 1;
	}

	// Create the socket address that the listening socket will be bound to
	std::cout << "Creating socket address for listening" << std::endl;
	SOCKADDR_IN addr;  // Address the listening socket will be bound to 
	int addrlen = sizeof(addr); // length of the address 
	addr.sin_addr.s_addr = INADDR_ANY;	// Accept any address
	addr.sin_port = htons(5000); // Port number
	addr.sin_family = AF_INET; // Defined as an IPv4 Socket

	// Create the socket to listen for new connections
	std::cout << "Creating socket to listen for new connections" << std::endl;
	SOCKET listen_socket = socket(AF_INET, SOCK_STREAM, 0); // socket to listen for new connections
	iResult = bind(listen_socket, (SOCKADDR*)&addr, sizeof(addr)); // Bind the address addr to the socket listen_socket
	if(iResult) {
		perror("Bind failed");
		system("pause");
		return 1;
	}
	iResult = listen(listen_socket, SOMAXCONN); // Set listen_socket into a listening state in which it listens for incoming connections, SOMAXCONN = socket maximum # of connections
	if(iResult) {
		perror("Listen failed");
		system("pause");
		return 1;
	}

	// Create a new socket to hold the clients connection (TCP) 
	std::cout << "Creating socket to hold clients connection" << std::endl;
	SOCKET client_socket;  // temporary socket for holding clients new connection
	client_socket = accept(listen_socket, (SOCKADDR*)&addr, &addrlen); // accept new connection

	if (client_socket == 0) {
		std::cout << "Failed to accept the client connection. " << std::endl; 
	}
	else {
		std::cout << "Client connected" << std::endl;
	}

	// Main loop - Receive data from client and process
	char buffer[BUFSIZ] = {0};
	std::string rawData;

	for(;;) {
		memset(buffer, 0, BUFSIZ);	// Clear buffer

		if(recv(client_socket, (char*)&buffer, sizeof(buffer), 0)) {
			rawData = buffer;	// Convert to C++ string
			std::cout << "Message from client: " << rawData << std::endl;
		}

		// Process [END] command which just shuts down communication
		if(!(rawData.compare("[END]"))) {
			std::cout << "Closing connection" << std::endl;
			closesocket(client_socket);
			closesocket(listen_socket);
			break;
		}

		// Process [REQ] command
		if((rawData.find("[REQ]") != std::string::npos)) {
			std::cout << "Person requested" << std::endl;
			person myPerson;					// For now just make a person up
			myPerson.sendPerson(client_socket);	// Send the person to the client
		}

		// Process [NEW] command
		if((rawData.find("[NEW]") != std::string::npos)) {
			std::cout << "New person received" << std::endl;
			person myPerson(rawData);	// Process that shit into a new person
			myPerson.printPerson();
			myPerson.printAddress();
		}
	}

	return 0;
}
