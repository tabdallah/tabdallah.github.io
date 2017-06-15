#include <iostream>
#include <cstdio>
#include <cstring>
#include <netinet/in.h>	// hostent and sockaddr structure def's
#include <netdb.h>		// gethostbyname function
#include <unistd.h>		// close()
#include "person.h"

#define PORT 5000	// Talk to the server using this port


// Main function
int main(int argc, char *argv[]) {
	
	// Global variables for main()
	std::string server_ip;
	struct sockaddr_in server_addr;
	struct hostent *host;
	int client_socket;
	int result;
	std::string myString;


	// Check that user provided an IP address as input
	if (argc < 2) {
		// Have user enter an IP address
		std::cout << "Please enter a server IP address: ";
		std::cin >> server_ip;
	}
	else {
		// Use address provided as input
		server_ip = argv[1];
	}

	// Get host info for the provided server
	std::cout << "Getting info for host at address: " << server_ip << std::endl;
	host = gethostbyname(server_ip.c_str());
	if(host == NULL) {
		perror("Could not get host info.");
		return 1;
	}

	// Get a socket
	std::cout << "Getting socket for client." << std::endl;
	client_socket = socket(AF_INET, SOCK_STREAM, 0);
	if(client_socket < 0) {
		perror("Could not get a socket.");
		return 1;
	}

	// Fill in server_addr structure
	memset(&server_addr, 0, sizeof(server_addr));
	server_addr.sin_family = AF_INET;
	memcpy(&server_addr.sin_addr.s_addr, host->h_addr, host->h_length);
	server_addr.sin_port = htons(PORT);

	// Try to connect to server
	std::cout << "Connecting to server." << std::endl;
	result = connect(client_socket, (struct sockaddr *)&server_addr, sizeof(server_addr));
	if(result < 0) {
		perror("Could not connect to server.");
		close(client_socket);
		return 1;
	}
	std::cout << "Connection successful." << std::endl;

	// Prompt user to create a new person
	person thomas;

	// Attempt to transmit person information to server
	thomas.sendPerson(client_socket);

	//write(client_socket, (char*) myString.c_str(), myString.length());

	close(client_socket);
	return(0);
}