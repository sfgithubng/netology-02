#include <iostream>
#include <string>

bool getBinaryChoice(std::string questionText, std::string failureText) {
    std::string userInputString{};
    char userInputChar{};
    std::string positiveAnswers = "Yy";
    std::string negativeAnswers = "Nn";
    while (1) {
        std::cout << questionText;
        std::getline(std::cin, userInputString);
        if (userInputString.length() > 1) {
            userInputString.clear();
            std::cout << failureText << std::endl;
            continue;
        }
        if (userInputString.length() == 0) {
            userInputString = 'Y';
        }
        try {
            userInputChar = userInputString[0];
        } catch (...) {
            std::cout << failureText << std::endl;
        }
        if (positiveAnswers.find(userInputChar) != std::string::npos) {
            return true;
        }
        if (negativeAnswers.find(userInputChar) != std::string::npos) {
            return false;
        }
        std::cout << failureText << std::endl;
    }
}

int32_t getInputIntVar(std::string questionText) {
    std::string userInputString{};
    int32_t userInputInt{};
    while (userInputString.empty()) {
        std::cout << questionText;
        std::getline(std::cin, userInputString);
        try {
            userInputInt = std::stoi(userInputString);
        } catch (...) {
            std::cout << "The '" + userInputString +
                             "' is not a valid number."
                      << std::endl;
            userInputString = "";
        }
    }
    return userInputInt;
}

char getInputCharVar(std::string questionText, std::string failureText) {
    std::string userInputString{};
    char userInputChar{};
    while (userInputString.empty()) {
        std::cout << questionText;
        std::getline(std::cin, userInputString);
        try {
            userInputChar = userInputString[0];
        } catch (...) {
            std::cout << failureText << std::endl;
            userInputString = "";
        }
    }
    return userInputChar;
}

class Counter {
private:
    int32_t value;
public:
    Counter() : value{1} {
    }

    Counter(int32_t constrValue) :
        value{constrValue} {
    }

    ~Counter() = default;

    Counter(const Counter& otherCounter) :
        Counter(otherCounter.value)
    {
    }

    void increment() {
        ++(this->value);
    }

    void decrement() {
        --(this->value);
    }

    void showValue() {
        std::cout << this->value << std::endl;
    }
};

int main() {
    bool useCustomCounterInitialValue = getBinaryChoice("Do you want to set counter initial value? [Y/n]: ", "Please input an answer from [YyNn]");
    int32_t counterInitialValue = useCustomCounterInitialValue ? getInputIntVar("Enter counter initial value: ") : 1;
    Counter counterInstance = useCustomCounterInitialValue ? Counter(counterInitialValue) : Counter();

    char controlCommand{'0'};
    while (controlCommand != 'x') {
        controlCommand = getInputCharVar("Enter command ('+', '-', '=' or 'x'): ", "Please input an answer from [+-=x]");
        switch (controlCommand) {
            case '+':
                counterInstance.increment();
            break;
            case '-':
                counterInstance.decrement();
            break;
            case '=':
                counterInstance.showValue();
            break;
        }
    }
    std::cout << "Bye!" << std::endl;

    return 0;
}