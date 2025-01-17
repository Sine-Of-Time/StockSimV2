#include "user.h"
#include <string>
#include <unordered_map>
#include "stock.h"
#include <stdexcept>
#include <iostream>

// Constructor
User::User(const std::string& username, int networth) : username(username), networth(networth), balance(0) {}

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

//Change this implementation -1/13/24
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

// Placeholder functions
void User::buyStock(Stock stock,int amountToBuy) {
    if ((stock.getTicker()).compare("Error") == 0) std::cout << "Stock selected to buy does not exist" << std::endl;
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