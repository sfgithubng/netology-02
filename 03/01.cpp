#include <iostream>
#include <string>

double getInputFractionalVar(std::string questionText) {
    std::string userInputString{};
    double userInputVar{};
    while (userInputString.empty()) {
        std::cout << questionText;
        std::getline(std::cin, userInputString);
        try {
            userInputVar = std::stold(userInputString);
        } catch (...) {
            std::cout << "The '" + userInputString +
                             "' is not a valid number."
                      << std::endl;
            userInputString = "";
        }
    }
    return userInputVar;
}

class Calculator {
private:
    double num1;
    double num2;
public:
    Calculator() = default;
    Calculator(double constrNum1, double constrNum2) :
        num1(constrNum1),
        num2(constrNum2) {
    }

    ~Calculator() = default;

    Calculator(const Calculator& otherCalculator) :
        Calculator(otherCalculator.num1, otherCalculator.num2)
    {
    }

    double add() {
        return this->num1 + this->num2;
    }

    double multiply() {
        return this->num1 * this->num2;
    }

    double subtract_1_2() {
        return this->num1 - this->num2;
    }

    double subtract_2_1() {
        return this->num2 - this->num1;
    }

    double divide_1_2() {
        return this->num1 / this->num2;
    }

    double divide_2_1() {
        return this->num2 / this->num1;
    }

    bool set_num1(double num1) {
        if (num1 == 0) {
            std::cout << "Incorrect input! Number must be non-zero for predictable results." << std::endl;
            return false;
        } else {
            this->num1 = num1;
            return true;
        }
    }

    bool set_num2(double num2) {
        if (num2 == 0) {
            std::cout << "Incorrect input! Number must be non-zero for predictable results." << std::endl;
            return false;
        } else {
            this->num2 = num2;
            return true;
        }
    }
};

int main() {
    while (1) {
        Calculator calcInstance;
        bool num1ValueSet{false};
        while (!num1ValueSet) {
            double num1Value = getInputFractionalVar("Enter num1: ");
            num1ValueSet = calcInstance.set_num1(num1Value);
        }
        bool num2ValueSet{false};
        while (!num2ValueSet) {
            double num2Value = getInputFractionalVar("Enter num2: ");
            num2ValueSet = calcInstance.set_num2(num2Value);
        }
        std::cout << "num1 + num2: " << calcInstance.add() << std::endl;
        std::cout << "num1 - num2: " << calcInstance.subtract_1_2() << std::endl;
        std::cout << "num2 - num1: " << calcInstance.subtract_2_1() << std::endl;
        std::cout << "num1 * num2: " << calcInstance.multiply() << std::endl;
        std::cout << "num1 / num2: " << calcInstance.divide_1_2() << std::endl;
        std::cout << "num2 / num1: " << calcInstance.divide_2_1() << std::endl;

    }

    return 0;
}
