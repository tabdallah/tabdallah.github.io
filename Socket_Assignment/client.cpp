#include <iostream>
#include <cstdio>
#include <cstring>
#include <netinet/in.h>	// hostent and sockaddr structure def's
#include <netdb.h>		// gethostbyname function
#include <unistd.h>		// close()
#include "client.h"

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
	int entry;


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

	for(;;) {
		std::cout << "----------------------------------" << std::endl;
		std::cout << "Enter '1' to enter a new person" << std:: endl;
		std::cout << "Enter '2' to request a specific person" << std:: endl;
		std::cout << "Enter anything else to exit" << std:: endl;
		std::cin >> entry;

		if(entry == 1) {
			person myPerson;					// Create a new person and send to the server
			myPerson.sendPerson(client_socket);	// Send the person to the server
		}
		else if(entry == 2) {
			int ID;

			std::cout << "Enter an ID number of person: ";
			std::cin >> ID;

			char buffer[BUFSIZ];

			// Write request & ID number to the server
			memset(buffer, 0, BUFSIZ);
			sprintf(buffer, "[REQ][%i]", ID);
			if(write(client_socket, &buffer, strlen(buffer)) < 1) {
				perror("Failed to write Request message");
			}

			// Read response data
			memset(buffer, 0, BUFSIZ);
			if(recv(client_socket, buffer, sizeof(buffer), 0) < 0) {
				perror("Did not receive persons data from server");
			}			

			// Process response data
			myString = buffer;
			person myPerson(myString);

			// Print persons data
			myPerson.printPerson();		// Print the persons name and ID number
			myPerson.printAddress();	// Print the persons address
		}
		else {
			std::string str_buffer = "[END]";
			write(client_socket, (char*)str_buffer.c_str(), str_buffer.length());
			break;
		}
	}


	close(client_socket);
	return(0);
}