#ifndef MANAGER_H
#define MANAGER_H

#include <string>
#include <unordered_map>
#include "stock.h"
#include <stack>
#include <vector>

class Manager {
private:
    bool showStockErrorTicker;

public:
    // Constructor
    Manager();

    // Main functions
    std::vector<std::string> initStock(const std::string tckr) const;
    void displayLine();
    void displayMainMenu();
    void searchForStock();

    // Getters
    Stock getStock(const std::string tckr) const;


    void setStockErrorTicker(bool status);

    // Destructor
    ~Manager();
};

#endif // MANAGER_H
