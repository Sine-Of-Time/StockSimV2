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
    std::string userName;
    short choice = 0;
    short choice2 = 0;
    short miscMenu = 0;
    Manager man;
    User user;
    man.loadUsers(USER_FILE);
    
    while (choice2!=1) {
        man.displayLogin();
        std::cin >> choice2;
        if (choice2 == 2) man.createUser();
        else {
            std::cout << "Please enter the name of the user you want to login:\n";
            std::cin >> userName;
            user = man.findUserByUsername(userName);
            if (user.getUsername() == "") choice2 = 0;
        }
    }

    do {
        char exitLoop = 'N';
        char buy = 'N';
        std::string tick;
        int amountOfStocks;

        man.displayMainMenu();
        std::cin >> choice;

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
            while (miscMenu != 3) {
                man.displayLine();
                man.miscMenu();
                std::cin >> miscMenu;
                if (miscMenu == 1) {
                   
                }
                if (miscMenu == 2) {
                    man.clearUsers();
                    user = User("", 0);
                    man.wipeFileData(USER_FILE);
                    return 0;
                }
                man.displayLine();
            }
            break;
        case 5://Exit
            choice = 5;
            std::cout << "Exiting Program!\n";
            break;
        default:
            std::cout << "Invalid choice. Please try again.\n";
            break;
        }
    } while (choice != 5); 

    man.addUser(user);
    man.saveUsers(USER_FILE);
    return 0;
}
