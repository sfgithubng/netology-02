#include <iostream>

enum class Months {
  January = 1,
  February = 2,
  March = 3,
  April = 4,
  May = 5,
  June = 6,
  July = 7,
  August = 8,
  September = 9,
  October = 10,
  November = 11,
  December = 12
};

int8_t getMonthInputIntVar(std::string questionText) {
  std::string userInputString{};
  int32_t userInputInt{};
  while (userInputString.empty()) {
    std::cout << questionText;
    std::getline(std::cin, userInputString);
    try {
      userInputInt = std::stoi(userInputString);
      if ((userInputInt < 0) || (userInputInt > 12)) {
        std::cout
            << "The number must be in [1, 12] range. Use 0 to exit. Please try again."
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
  return userInputInt;
}

int main() {
  int8_t monthNumber{100};
  while (monthNumber != 0) {
    monthNumber = getMonthInputIntVar("Enter the month number: ");
    Months userMonth{monthNumber};
    switch(userMonth)
    {
      case Months::January:
        std::cout << "January\n";
      break;
      case Months::February:
        std::cout << "February\n";
      break;
      case Months::March:
        std::cout << "March\n";
      break;
      case Months::April:
        std::cout << "April\n";
      break;
      case Months::May:
        std::cout << "May\n";
      break;
      case Months::June:
        std::cout << "June\n";
      break;
      case Months::July:
        std::cout << "July\n";
      break;
      case Months::August:
        std::cout << "August\n";
      break;
      case Months::September:
        std::cout << "September\n";
      break;
      case Months::October:
        std::cout << "October\n";
      break;
      case Months::November:
        std::cout << "November\n";
      break;
      case Months::December:
        std::cout << "December\n";
      break;
    }
  }
  std::cout << "See you!";

  return 0;
}