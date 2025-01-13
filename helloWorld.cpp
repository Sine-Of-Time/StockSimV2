#include <iostream>
#include <vector>
#include <string>
#include "Manager.h"
#include <iomanip>
#include <algorithm>

std::vector<double> yValues = {};

int main() { //This main will be the graph display code
    Manager man;
    Stock st = man.getStock("AAPL");
    st.displayData();

    return 0;
}


