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
    double balance;
    double networth;
    bool showMsg = false;

    //Private functions
    void calculateNetworth();

public:
    // Constructor
    User(const std::string& username = "", double balance = 0.0);

    void adjustBalance();
    void increaseBalanceBy(int increase);
    void decreaseBalanceBy(int decrease);
    void buyStock(Stock stock, int amountToBuy);
    void sellStock(std::string ticker, int amountToSell);
    void displayPortfolio() const;
    void displayUserData();
    void addStock(const Stock& stock);

    // Getters
    std::string getUsername() const;
    int getNetworth() const;
    int getBalance() const; 
    const std::unordered_map<std::string, Stock>& getPortfolio() const;
    Stock getStockByTicker(const std::string& ticker) const;

    // Setters
    void setUsername(const std::string& username);
    void setNetworth(int networth);
    void setBalance(int balance); 
};
#endif // USER_H