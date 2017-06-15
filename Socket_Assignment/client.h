/* Header file for the person class */
#include <cstdio>
#include <cstdlib>

/* Creating a class to hold all the information about a person for this assignment */
class person {
public:
	// Data manipulator functions
	void setID(unsigned int number);
	void setName(std::string name);
	void setStNumber(unsigned int number);
	void setStName(std::string name);
	void setCity(std::string name);
	void setProvince(std::string province);
	void setCountry(std::string country);
	void setPostCode(std::string code);

	// Accessor functions
	void printPerson();		// Print persons name and ID number
	void printAddress();	// Print peresons address
	void sendPerson(int socket);		// Send all data about person to server over socket

	// Constructors
	person();			// Default - asks user to enter details of a person
	person(int option);	// Makes a blank person, or a person with an ID number
	person(std::string rawData);	// Make a new person based on raw data from the server


private:
	unsigned int ID;		// ID number of person
	std::string Name;		// Name of person	
	unsigned int StNumber;	// Address - Street Number
	std::string StName;		// Address - Street Name
	std::string City;		// Address - City Name
	std::string Province;	// Address - Province Name
	std::string Country;	// Address - Country Name
	std::string PostCode;	// Address - Postal Code	
};

void person::setID(unsigned int number) {
	ID = number;
}

/* Functions for the person class */
void person::setName(std::string name) {
	Name = name;
}

void person::setStNumber(unsigned int number) {
	StNumber = number;
}

void person::setStName(std::string name) {
	StName = name;
}

void person::setCity(std::string name) {
	City = name;
}

void person::setProvince(std::string province) {
	Province = province;
}

void person::setCountry(std::string country) {
	Country = country;
}

void person::setPostCode(std::string code) {
	PostCode = code;
}

void person::printPerson() {
	std::cout << "ID: " << ID << std::endl;
	std::cout << "Name: " << Name << std::endl;	
}

void person::printAddress() {
	std::cout << "Address:" << std::endl;
	std::cout << StNumber << " " << StName << std::endl;
	std::cout << City << ", " << Province << ", " << Country << std::endl;
	std::cout << PostCode << std::endl;
}

void person::sendPerson(int socket) {
	char buffer[BUFSIZ];

	// Write data into a buffer
	memset(buffer, 0, BUFSIZ);
	sprintf(buffer, "[NEW][%i][%s][%i][%s][%s][%s][%s][%s]", ID, (char*)Name.c_str(), 
		StNumber, (char*)StName.c_str(), (char*)City.c_str(), 
		(char*)Province.c_str(), (char*)Country.c_str(), (char*)PostCode.c_str());

	if(write(socket, &buffer, strlen(buffer)) < 1) {
		perror("Failed to write New person data");
	}
}
person::person() {
	std::cout << "Creating a new person." << std::endl;

	std::cout << "Enter ID number: ";
	std::cin >> ID;

	std::cout << "Enter name: ";
	std::cin.ignore();	// Flush std input
	std::getline(std::cin, Name);

	std::cout << "Enter Street Number: ";
	std::cin >> StNumber;

	std::cout << "Enter Street Name: ";
	std::cin.ignore();	// Flush std input
	std::getline (std::cin, StName);

	std::cout << "Enter City Name: ";
	std::cin >> City;

	std::cout << "Enter Province Name: ";
	std::cin >> Province;

	std::cout << "Enter Country Name: ";
	std::cin >> Country;

	std::cout << "Enter Postal Code: ";
	std::cin >> PostCode;
}

person::person(int option) {
	if(!option) {
		std::cout << "Creating a new blank person." << std::endl;	
	}
	else {
		std::cout << "Enter ID number for person." << std::endl;
		std::cin >> ID;
	}
}

person::person(std::string rawData) {
	std::string delimiter = "][";
	int pos;

	// Get rid of the [NEW] tag at the beginning.
	pos = rawData.find(delimiter);
	rawData = rawData.substr(pos + 2, std::string::npos);
	
	// Parse the ID number
	pos = rawData.find(delimiter);
	ID = atoi(rawData.substr(0, pos).c_str());
	rawData = rawData.substr(pos + 2, std::string::npos);
	
	// Parse the Name
	pos = rawData.find(delimiter);
	Name = rawData.substr(0, pos);
	rawData = rawData.substr(pos + 2, std::string::npos);

	// Parse the Street Number
	pos = rawData.find(delimiter);
	StNumber = atoi(rawData.substr(0, pos).c_str());
	rawData = rawData.substr(pos + 2, std::string::npos);

	// Parse the StName
	pos = rawData.find(delimiter);
	StName = rawData.substr(0, pos);
	rawData = rawData.substr(pos + 2, std::string::npos);

	// Parse the City
	pos = rawData.find(delimiter);
	City = rawData.substr(0, pos);
	rawData = rawData.substr(pos + 2, std::string::npos);

	// Parse the Province
	pos = rawData.find(delimiter);
	Province = rawData.substr(0, pos);
	rawData = rawData.substr(pos + 2, std::string::npos);

	// Parse the Country
	pos = rawData.find(delimiter);
	Country = rawData.substr(0, pos);
	rawData = rawData.substr(pos + 2, std::string::npos);

	// Parse the Postal Code
	PostCode = rawData.substr(0, rawData.length() - 1);	// pos-1 to strip off the trailing ']' at the end of the raw data
}
