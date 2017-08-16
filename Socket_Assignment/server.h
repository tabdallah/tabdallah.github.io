/* Header file for the person class */
#include <cstdio>
#include <fstream>  

/* Creating a class to hold all the information about a person for this assignment */
class person {
public:
	// Data manipulator functions
	void setID(int number);
	void setName(std::string name);
	void setStNumber(int number);
	void setStName(std::string name);
	void setCity(std::string name);
	void setProvince(std::string province);
	void setCountry(std::string country);
	void setPostCode(std::string code);

	// Accessor functions
	void printPerson();		// Print persons name and ID number
	void printAddress();	// Print peresons address
	void sendPerson(int socket);		// Send all data about person to server over socket
	void getPerson(int socket);			// Request data on a specific person from the server
	void addToFile();		// Add person to the CSV file
	void getDataFromCSV();	// Populate the rest of the data from CSV file

	// Constructors
	person();			// Default - asks user to enter details of a person
	person(int option);	// Makes a blank person, or a person with an ID number
	person(std::string rawData);	// Makes a new person based on raw input from client

private:
	int ID;		// ID number of person
	std::string Name;		// Name of person	
	int StNumber;	// Address - Street Number
	std::string StName;		// Address - Street Name
	std::string City;		// Address - City Name
	std::string Province;	// Address - Province Name
	std::string Country;	// Address - Country Name
	std::string PostCode;	// Address - Postal Code	
};

void person::setID(int number) {
	ID = number;
}

/* Functions for the person class */
void person::setName(std::string name) {
	Name = name;
}

void person::setStNumber(int number) {
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

	if(send(socket, (char*)&buffer, strlen(buffer), 0) < 1) {
		perror("Failed to write New person data");
	}
}

void person::getPerson(int socket) {
	char buffer[BUFSIZ];
	std::string myString;

	// Write request & ID number to the server
	memset(buffer, 0, BUFSIZ);
	sprintf(buffer, "[REQ][%i]", ID);
	if(send(socket, (char*)&buffer, strlen(buffer), 0) < 1) {
		perror("Failed to write Request message");
	}

	// Read response data
	memset(buffer, 0, BUFSIZ);
	if(recv(socket, buffer, sizeof(buffer), 0) < 0) {
		perror("Did not receive persons data from server");
	}

	// Parse persons data
	myString = buffer;
	std::cout << "String: " << myString << std::endl;

}

void person::addToFile() {

	// Open file in append mode
	std::ofstream myFile;
	myFile.open("people.csv", std::ofstream::out | std::ofstream::app);
	if(myFile.fail()) {
		perror("Failed to open file");
		return;
	}

	myFile << ID << "," << Name << "," << StNumber << "," << StName << "," <<
		City << "," << Province << "," << Country << "," << PostCode << "," << "\n";

	myFile.close();
}

void person::getDataFromCSV() {
	// Open file in read mode
	std::ifstream myFile;
	myFile.open("people.csv", std::ofstream::in);

	if(myFile.fail()) {
		perror("Failed to open file");
		return;
	}

	std::string data;
	int id;

	while(!myFile.eof()) {
		// Read ID (first column in each line)
		getline(myFile, data, ',');
		id = atoi(data.c_str());

		if(id == ID) {
			std::cout << "Found requested person in CSV file" << std::endl;
			getline(myFile, Name, ',');	// Read Name
			getline(myFile, data, ',');	// Read Street Number
			StNumber = atoi(data.c_str());
			getline(myFile, StName, ',');	// Read Street Name
			getline(myFile, City, ',');	// Read City
			getline(myFile, Province, ',');	// Read Province
			getline(myFile, Country, ',');	// Read Country
			getline(myFile, PostCode, ',');	// Read Postal Code
			break;
		}
		else{
			// Read the other elements on this line so we don't mistake them for an ID
			getline(myFile, data, ',');	// 2nd column = Name
			getline(myFile, data, ','); // 3rd column = St Number
			getline(myFile, data, ','); // 4th column = St Name
			getline(myFile, data, ','); // 5th column = City
			getline(myFile, data, ','); // 6th column = Province
			getline(myFile, data, ','); // 7th column = Country 
			getline(myFile, data, ','); // 8th column = Postal Code
		}
	}

	myFile.close();
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