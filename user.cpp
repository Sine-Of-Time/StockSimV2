#include "user.h"
#include <string>
#include <unordered_map>
#include "stock.h"
#include <stdexcept>

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
    auto it = portfolio.find(ticker);
    if (it != portfolio.end()) {
        return it->second;
    }
    throw std::runtime_error("Stock with ticker " + ticker + " not found in portfolio.");
}

// Placeholder functions
void User::buyStock() {
    // To be implemented
}

void User::sellStock() {
    // To be implemented
}