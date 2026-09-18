#include <iostream>
#include <vector>
#include <string>
#include <cmath>
#include <limits>
#include <sstream>
#include <iomanip>

class Calculator {
private:
    std::vector<std::string> history;
    const size_t MAX_HISTORY = 10;

    void addHistory(const std::string& entry) {
        if (history.size() >= MAX_HISTORY) {
            history.erase(history.begin());
        }
        history.push_back(entry);
    }


    bool readDouble(double& val, const std::string& prompt) {
        while (true) {
            std::cout << prompt;
            if (std::cin >> val) {
                return true;
            }
            
            
            std::cin.clear(); 
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); 
            std::cout << "Invalid input! Please enter a valid numerical value.\n";
        }
    }

public:
    void printHistory() const {
        std::cout << "\n====================================\n";
        std::cout << "       LAST 10 CALCULATIONS         \n";
        std::cout << "====================================\n";
        if (history.empty()) {
            std::cout << " No calculations recorded yet.\n";
        } else {
            for (size_t i = 0; i < history.size(); ++i) {
                std::cout << " " << std::setw(2) << i + 1 << ". " << history[i] << "\n";
            }
        }
        std::cout << "====================================\n\n";
    }

    void run() {
        while (true) {
            std::cout << "\n------------------------------------\n";
            std::cout << " [1] Perform Calculation\n";
            std::cout << " [2] Print Last 10 Calculations\n";
            std::cout << " [3] Quit\n";
            std::cout << "------------------------------------\n";
            std::cout << "Select an option (1-3): ";

            int choice;
            if (!(std::cin >> choice)) {
                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                std::cout << "Invalid menu selection. Please enter 1, 2, or 3.\n";
                continue;
            }

            if (choice == 3) {
                std::cout << "Exiting calculator. Goodbye!\n";
                break;
            } else if (choice == 2) {
                printHistory();
                continue;
            } else if (choice != 1) {
                std::cout << "Invalid option. Please choose 1, 2, or 3.\n";
                continue;
            }

            
            double num1, num2, result;
            char op;

            readDouble(num1, "Enter first number: ");

    
            while (true) {
                std::cout << "Enter operator (+, -, *, /, %, ^): ";
                std::cin >> op;

                if (op == '+' || op == '-' || op == '*' || op == '/' || op == '%' || op == '^') {
                    break;
                }
                std::cout << "Invalid operator! Supported operators are +, -, *, /, %, ^\n";
            }

            readDouble(num2, "Enter second number: ");


            bool validOperation = true;
            std::string errorMsg = "";

            switch (op) {
                case '+': 
                    result = num1 + num2; 
                    break;
                case '-': 
                    result = num1 - num2; 
                    break;
                case '*': 
                    result = num1 * num2; 
                    break;
                case '/':
                    if (num2 == 0) {
                        validOperation = false;
                        errorMsg = "Error: Division by zero!";
                    } else {
                        result = num1 / num2;
                    }
                    break;
                case '%':
                    if (num2 == 0) {
                        validOperation = false;
                        errorMsg = "Error: Modulo by zero!";
                    } else {
                        result = std::fmod(num1, num2);
                    }
                    break;
                case '^':
                    result = std::pow(num1, num2);
                    if (std::isnan(result) || std::isinf(result)) {
                        validOperation = false;
                        errorMsg = "Error: Invalid power operation (undefined result)!";
                    }
                    break;
            }

            if (validOperation) {
                std::cout << ">>> Result: " << result << "\n";
                
                std::ostringstream ss;
                ss << num1 << " " << op << " " << num2 << " = " << result;
                addHistory(ss.str());
            } else {
                std::cout << ">>> " << errorMsg << "\n";
            }
        }
    }
};

int main() {
    Calculator calc;
    calc.run();
    return 0;
}