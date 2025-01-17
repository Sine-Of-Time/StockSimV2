#ifndef MANAGER_H
#define MANAGER_H

#include <string>
#include <unordered_map>
#include "stock.h"
#include <stack>
#include <vector>

class Manager {
private:

public:
    // Constructor
    Manager();

    // Main functions
    std::vector<std::string> initStock(const std::string tckr) const;
    void displayLine();
    void displayMainMenu();

    // Getters
    Stock getStock(const std::string tckr) const;

    // Destructor
    ~Manager();
};

#endif // MANAGER_H
