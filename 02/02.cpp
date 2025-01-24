#include <iostream>
#include <limits>

struct BankAccount {
    u_int32_t number{0};
    std::string holderName;
    long double balanceFunds{0.0f};
};

void updateBankAccountNumber(BankAccount *userBankAccount, std::string questionText) {
    std::string userInputString{};
    u_int64_t userInputInt{};
    while (userInputString.empty()) {
        std::cout << questionText;
        std::getline(std::cin, userInputString);
        try {
            userInputInt = std::stoi(userInputString);
            if ((userInputInt < 0) || (userInputInt > std::numeric_limits<u_int32_t>::max() - 1)) {
                std::cout
                    << "The number must be in [0, " << (std::numeric_limits<u_int32_t>::max() - 1) << "] range. Please try again."
                    << std::endl;
                userInputString = "";
            }
        } catch (...) {
            std::cout << "The '" + userInputString +
                             "' is not a valid number."
                      << std::endl;
            userInputString = "";
        }
    }
    userBankAccount->number = static_cast<u_int32_t>(userInputInt);
}

void updateBankAccountBalance(BankAccount *userBankAccount, std::string questionText) {
    std::string userInputString{};
    long double userInputLongDouble{};
    while (userInputString.empty()) {
        std::cout << questionText;
        std::getline(std::cin, userInputString);
        try {
            userInputLongDouble = std::stold(userInputString);
            if ((userInputLongDouble < 0) || (userInputLongDouble > std::numeric_limits<long double>::max() - 1)) {
                std::cout
                    << "The number must be in [0, " << (std::numeric_limits<long double>::max() - 1) << "] range. Please try again."
                    << std::endl;
                userInputString = "";
            }
        } catch (...) {
            std::cout << "The '" + userInputString +
                             "' is not a valid number."
                      << std::endl;
            userInputString = "";
        }
    }
    userBankAccount->balanceFunds = userInputLongDouble;
}

void updateBankAccountName(BankAccount *userBankAccount, std::string questionText) {
    std::string userInputString{};
    while (userInputString.empty()) {
        std::cout << questionText;
        std::getline(std::cin, userInputString);
    }
    userBankAccount->holderName = userInputString;
}

int main() {
    BankAccount userBankAccount;
    updateBankAccountNumber(&userBankAccount, "Please enter bank account number: ");
    updateBankAccountName(&userBankAccount, "Please enter account holder name: ");
    updateBankAccountBalance(&userBankAccount, "Please enter account balance: ");
    updateBankAccountBalance(&userBankAccount, "Please enter updated account balance: ");
    std::cout << "Your account: " << userBankAccount.holderName << ", " << userBankAccount.number << ", " << userBankAccount.balanceFunds;

    return 0;
}