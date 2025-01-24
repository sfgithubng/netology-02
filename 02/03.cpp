#include <iostream>
#include <vector>

struct PostalAddress {
    std::string city;
    std::string street;
    u_int16_t houseNumber{0};
    u_int16_t apartmentNumber{0};
    std::string postCode;
};

void printAddressArray(std::vector<PostalAddress> *postalAddresses) {
    for (auto postalAddressEntry : *postalAddresses) {
        std::cout << "City: " << postalAddressEntry.city << std::endl;
        std::cout << "Street: " << postalAddressEntry.street << std::endl;
        std::cout << "House No: " << postalAddressEntry.houseNumber << std::endl;
        std::cout << "Apartment No: " << postalAddressEntry.apartmentNumber << std::endl;
        std::cout << "Postcode: " << postalAddressEntry.postCode << std::endl;
        std::cout << std::endl;
    }
}

int main() {
    PostalAddress addressN1 {"Moscow", "Arbat", 12, 8, "123456"};
    PostalAddress addressN2 {"Izhevsk", "Pushkina", 59, 143, "953769"};
    std::vector<PostalAddress> postalAddresses{};
    postalAddresses.push_back(addressN1);
    postalAddresses.push_back(addressN2);
    printAddressArray(&postalAddresses);

    return 0;
}