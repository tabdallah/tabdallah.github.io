/* Header file for the person class */
#include <stdio>

/* Creating a class to hold all the information about a person for this assignment */
class person {
public:
	// Data manipulator functions
	void setName(std::string name);
	void setID(unsigned int number);
	void setStNumber(unsigned int number);
	void setStName(std::string name);
	void setCity(std::string name);
	void setPostCode(std::string code);
	void setProvince(std::string province);
	void setCountry(std::string country);

	// Accessor functions
	void printPerson();		// Print persons name and ID number
	void printAddress();	// Print peresons address

	// Constructor
	person();

private:
	std::string Name;		// Name of person
	unsigned int ID;		// ID number of person
	unsigned int StNumber;	// Address - Street Number
	std::string StName;		// Address - Street Name
	std::string City;		// Address - City Name
	std::string PostCode;	// Address - Postal Code
	std::string Province;	// Address - Province Name
	std::string Country;	// Address - Country Name
};

/* Functions for the person class */
void person::setName(std::string name) {
	Name = name;
}

void person::setID(unsigned int number) {
	ID = number;
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

void person::setPostCode(std::string code) {
	PostCode = code;
}

void person::setProvince(std::string province) {
	Province = province;
}

void person::setCountry(std::string country) {
	Country = country;
}

void person::printPerson() {
	std::cout << "Name: " << Name << std::endl;
	std::cout << "ID: " << ID << std::endl;
}

void person::printAddress() {
	std::cout << "Address:" << std::endl;
	std::cout << StNumber << " " << StName << std::endl;
	std::cout << City << ", " << Province << ", " << Country << std::endl;
	std::cout << PostCode << std::endl;
}

person::person() {
	std::cout << "Creating a new person." << std::endl;
	
	std::cout << "Enter name: ";
	std::getline(std::cin, Name);

	std::cout << "Enter ID number: ";
	std::cin >> ID;

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