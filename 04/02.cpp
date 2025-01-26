#include <algorithm>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include <iterator>

const int8_t inputFileLinesForAddress = 4;

class Address {
private:
    std::string city;
    std::string street;
    int8_t houseNo;
    int8_t apartmentNo;
public:
    Address() = default;

    Address(std::string constrCity, std::string constrStreet, int8_t constrHouseNo, int8_t constrApartmentNo) :
        city{constrCity},
        street{constrStreet},
        houseNo{constrHouseNo},
        apartmentNo{constrApartmentNo} {
    }

    ~Address() = default;

    Address(const Address& otherAddress) :
        city{otherAddress.city},
        street{otherAddress.street},
        houseNo{otherAddress.houseNo},
        apartmentNo{otherAddress.apartmentNo} {
    }

    std::string getFullAddress() {
        return (this->city + ", " + this->street + ", " + std::to_string(this->houseNo) + ", " + std::to_string(this->apartmentNo) + "\n");
    }
};

int main() {
    std::string inFilename = "in.txt";
    std::string lineFromInFile;
    std::vector<Address> addressesFromFile{};
    std::ifstream inFileStream;
    inFileStream.open(inFilename);
    int8_t addressesInFile{0};
    if (inFileStream.is_open()) {
        int8_t linesRead{0};
        std::string cityFromFile;
        std::string streetFromFile;
        int8_t houseNoFromFile;
        int8_t apartmentNoFromFile;
        std::getline(inFileStream, lineFromInFile);
        addressesInFile = std::stoi(lineFromInFile);
        while (std::getline(inFileStream, lineFromInFile)) {
            switch (linesRead) {
                case 0:
                    cityFromFile = lineFromInFile;
                break;
                case 1:
                    streetFromFile = lineFromInFile;
                break;
                case 2:
                    houseNoFromFile = std::stoi(lineFromInFile);
                break;
                case 3:
                    apartmentNoFromFile = std::stoi(lineFromInFile);
                break;
            }
            ++linesRead;
            if (linesRead == inputFileLinesForAddress) {
                addressesFromFile.push_back(Address(cityFromFile, streetFromFile, houseNoFromFile, apartmentNoFromFile));
                linesRead = 0;
            }
        }
        inFileStream.close();
    } else {
        std::cout << "Encountered an error while accessing in.txt, please check if the file exists" << std::endl;
    }

    std::vector<std::string> outputAddresses{};
    for (std::vector<Address>::iterator addressEntryIterator = addressesFromFile.begin();
         addressEntryIterator != addressesFromFile.end();
         ++addressEntryIterator) {
        outputAddresses.push_back(addressEntryIterator->getFullAddress());
    }

    std::sort(outputAddresses.begin(), outputAddresses.end());

    std::string outFilename = "out.txt";
    std::ofstream outFileStream;
    outFileStream.open(outFilename);
    if (outFileStream.is_open()) {
        outFileStream << addressesInFile;
        for (std::vector<std::string>::iterator addressEntryIterator = outputAddresses.begin();
             addressEntryIterator != outputAddresses.end();
             ++addressEntryIterator) {
            outFileStream << *addressEntryIterator;
        }
        outFileStream.close();
    }

    return 0;
}