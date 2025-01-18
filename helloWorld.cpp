#define USER_FILE "User.txt"

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
    //user = man.loadUserData("User.txt");
    //user.displayPortfolio();
    //user.displayUserData();

    user.setBalance(234);
    user.setNetworth(432);
    user.setUsername("Testing");
    man.saveUserData(user,"User.txt");
    
    
    
    

    /*
    do {
        man.displayMainMenu();
        std::cin >> choice;

        char exitLoop = 'N';
        char buy = 'N';
        std::string tick;
        int amountOfStocks;
        switch (choice) {
        case 1://Seach for stocks
            man.displayLine();
            man.searchForStock();
            std::cout << "Which stock would you like to buy?(exit to skip):";
            std::cin >> tick;
            if (tick.compare("exit") == 0) {
                std::cout << "Goodbye\n";
                break;
            }
            std::cout << "Please enter the amount you would like to buy:\n";
            std::cin >> amountOfStocks;
            user.buyStock(man.getStock(tick), amountOfStocks);
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
    } while (choice != 4); */
    return 0;
}
