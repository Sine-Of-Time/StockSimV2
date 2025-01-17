#ifndef MANAGER_H
#define MANAGER_H

#include <string>
#include <unordered_map>
#include "stock.h"
#include <stack>
#include <vector>

class Manager {
private:
    //std::string companyName;
    //std::string ticker;
   

public:
    // Constructor
    Manager();

    // Main functions
    std::vector<std::string> initStock(const std::string tckr) const;

    // Getters
    Stock getStock(const std::string tckr) const;

    // Destructor
    ~Manager();
};

#endif // MANAGER_H
