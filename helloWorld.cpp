#include <iostream>
#include <vector>
#include <string>
#include "Manager.h"
#include <iomanip>
#include <algorithm>
#include <limits>
#include <json/json.h>
#include "user.h"
#include "curl_function.h"

int main() {
    short choice = 0;
    Manager man;
    User user;

    do {
        man.displayMainMenu();
        std::cin >> choice;

        char exitLoop = 'N';
        switch (choice) {
        case 1://Seach for stocks
            man.displayLine();
            man.searchForStock();
            //TO DO BY/SELL f(x) -KF 1/17/24
            man.displayLine();
            break;
        case 2://Display portfolio
            man.displayLine();;
            user.displayPortfolio();
            man.displayLine();
            break;
        case 3://Display user data/adj balance
            while (exitLoop == 'N') {
                man.displayLine();
                user.displayUserData();
                user.adjustBalance();
                std::cout << "Would you like to return to main menu? Y/N?" << std::endl;
                std::cin >> exitLoop;
                man.displayLine();
            }
            break;
        case 4://Exit
            choice = 4;
            std::cout << "Exiting Program!\n";
            break;
        default:
            std::cout << "Invalid choice. Please try again.\n";
            break;
        }
    } while (choice != 4);
    return 0;
}
