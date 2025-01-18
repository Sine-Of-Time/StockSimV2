#include "user.h"
#include <string>
#include <limits> // For input validation
#include <unordered_map>
#include "stock.h"
#include <stdexcept>
#include <iostream>
#include <iomanip> // For formatting output

// Constructor
User::User(const std::string& username, int networth) : username(username), networth(networth), balance(0) {}

Stock User::getStockByTicker(const std::string& ticker) const {
    try {
        Stock stock = portfolio.at(ticker); // Throws an exception
        return stock;
    }
    catch (const std::out_of_range& e) {
        std::cout << "Ticker " << ticker << " does not exist to be returned: " << e.what() << std::endl;
        return Stock();
    }
}

void User::buyStock(Stock stock,int amountToBuy) {
    if ((stock.getTicker()).compare("Error") == 0) {
        std::cout << "Stock selected to buy does not exist" << std::endl;
        return;
    }
    try {
        Stock stockTmp = portfolio.at(stock.getTicker()); // Throws an exception
        stockTmp.increaseIssuedQuantityBy(amountToBuy);
        std::cout << "Brought " << amountToBuy << " shares of " << stockTmp.getCompanyName() << "increasing it to" << stockTmp.getIssuedQuantity() << std::endl;
    }
    catch (const std::out_of_range& e) {
        stock.increaseIssuedQuantityBy(amountToBuy);
        portfolio[stock.getTicker()] = stock;
        std::cout << "Added Stock " << stock.getCompanyName() <<  " to your portfolio by buying " << amountToBuy << " shares!" << std::endl;
    }
}

void User::sellStock(std::string ticker,int amountToSell) {
    try {
        Stock stock = portfolio.at(ticker); // Throws an exception
        if(stock.getIssuedQuantity()<amountToSell){
            std::cout << "Amount of stocks selected to be sold exceeds amount you own. Thus you can not sell " << amountToSell << " shares of " << stock.getCompanyName() << std::endl;
            return;
        }
        int prevShares = stock.getIssuedQuantity();
        stock.decreaseIssuedQuantityBy(amountToSell);
        std::cout << "Sold " << amountToSell << " shares of " << stock.getCompanyName() << " taking your shares from "<< prevShares <<" to "<< stock.getIssuedQuantity() << std::endl;
    }
    catch (const std::out_of_range& e) {
        std::cout << "Ticker "<< ticker << " does not exist to be sold: " << e.what() << std::endl;
    }
}

void User::adjustBalance() {
    int choice = 0;
    int amount = 0;
    std::cout << "----------------------------------------------------------\n";
    std::cout << "Would you like to:\n";
    std::cout << "1. Increase Balance\n";
    std::cout << "2. Decrease Balance\n";
    std::cout << "3. Do Nothing\n";
    std::cout << "Enter your choice (1, 2, or 3): ";
    std::cin >> choice;

    // Input validation
    while (std::cin.fail() || (choice < 1 || choice > 3)) {
        std::cin.clear(); // Clear the error flag
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Ignore invalid input
        std::cout << "Invalid input. Please enter 1, 2, or 3: ";
        std::cin >> choice;
    }

    if (choice == 1) {
        std::cout << "Enter the amount to increase: ";
        std::cin >> amount;

        // Input validation for amount
        while (std::cin.fail() || amount <= 0) {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "Invalid input. Please enter a positive amount: ";
            std::cin >> amount;
        }

        increaseBalanceBy(amount);
        std::cout << "Your balance has been increased by $" << amount << ".\n";
    }
    else if (choice == 2) {
        std::cout << "Enter the amount to decrease: ";
        std::cin >> amount;

        // Input validation for amount
        while (std::cin.fail() || amount <= 0) {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "Invalid input. Please enter a positive amount: ";
            std::cin >> amount;
        }

        if (amount > balance) {
            std::cout << "Insufficient funds. Cannot decrease balance by $" << amount << ".\n";
        }
        else {
            decreaseBalanceBy(amount);
            std::cout << "Your balance has been decreased by $" << amount << ".\n";
        }
    }
    else if (choice == 3) {
        std::cout << "No changes made to your balance.\n";
    }

    std::cout << "Your current balance is: $" << balance << ".\n";
    std::cout << "----------------------------------------------------------\n";
}

void User::displayPortfolio() const {
    if (portfolio.empty()) {
        std::cout << "Your portfolio is empty.\n";
        return;
    }

    std::cout << "Portfolio Overview:\n";
    std::cout << std::left << std::setw(20) << "Company Name"
        << std::setw(10) << "Ticker"
        << std::setw(10) << "Value"
        << std::setw(15) << "Issued Quantity\n";

    std::cout << std::string(55, '-') << "\n"; // Separator line

    for (const auto& [ticker, stock] : portfolio) {
        std::cout << std::left << std::setw(20) << stock.getCompanyName()
            << std::setw(10) << stock.getTicker()
            << std::setw(10) << stock.getValue()
            << std::setw(15) << stock.getIssuedQuantity() << "\n";
    }
}

void User::displayUserData() const {
    std::cout << "User Information:\n";
    std::cout << "------------------\n";
    std::cout << "Username: " << username << "\n";
    std::cout << "Balance: $" << balance << "\n";
    std::cout << "Net Worth: $" << networth << "\n";
    std::cout << "------------------\n";
}

void User::increaseBalanceBy(int increase) {
    balance = balance + increase;
}

void User::decreaseBalanceBy(int decrease) {
    balance = balance - decrease;
}

// Getters
std::string User::getUsername() const {
    return username;
}

int User::getNetworth() const {
    return networth;
}

int User::getBalance() const {
    return balance;
}

const std::unordered_map<std::string, Stock>& User::getPortfolio() const{
    return portfolio;
}

// Setters
void User::setUsername(const std::string& username) {
    this->username = username;
}

void User::setNetworth(int networth) {
    this->networth = networth;
}

void User::setBalance(int balance) {
    this->balance = balance;
}
