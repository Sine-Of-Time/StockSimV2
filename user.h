// user.h
#ifndef USER_H
#define USER_H

#include <string>
#include <unordered_map>
#include "stock.h"

class User {
private:
    std::string username;
    std::unordered_map<std::string, Stock> portfolio;
    int balance;
    int networth;

public:
    // Constructor
    User(const std::string& username = "", int networth = 0);

    // Getters
    std::string getUsername() const;
    int getNetworth() const;
    int getBalance() const; // Getter for balance

    // Setters
    void setUsername(const std::string& username);
    void setNetworth(int networth);
    void setBalance(int balance); // Setter for balance

    // Function to get a stock based on a ticker
    Stock getStockByTicker(const std::string& ticker) const;

    // Placeholder functions
    void buyStock();
    void sellStock();
};

#endif // USER_H