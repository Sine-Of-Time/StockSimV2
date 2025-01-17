#include <iostream>
#include <vector>
#include <string>
#include "Manager.h"
#include <iomanip>
#include <algorithm>
#include "user.h"

std::vector<double> yValues = {};

int main() { //This main will be the graph display code
    Manager man;
    Stock st = man.getStock("AAPL");
    User user;
    user.buyStock(st, 25);
    Stock st2 = user.getStockByTicker("AAPL");
    user.sellStock("AAPL", 20);
    std::cout << "Hello wrld" << std::endl;
    user.sellStock("2sda", 20);
    user.sellStock("AAPL", 200);
    return 0;
}


