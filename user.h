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

    void adjustBalance();
    Stock getStockByTicker(const std::string& ticker) const;
    void increaseBalanceBy(int increase);
    void decreaseBalanceBy(int decrease);
    void buyStock(Stock stock, int amountToBuy);
    void sellStock(std::string ticker, int amountToSell);
    void displayPortfolio() const;
    void displayUserData() const;

    // Getters
    std::string getUsername() const;
    int getNetworth() const;
    int getBalance() const; 
    const std::unordered_map<std::string, Stock>& getPortfolio() const;

    // Setters
    void setUsername(const std::string& username);
    void setNetworth(int networth);
    void setBalance(int balance); 
};

#endif // USER_H