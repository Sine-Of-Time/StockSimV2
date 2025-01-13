#include <iostream>
#include <vector>
#include <string>
#include "Manager.h"


int main() {
    Manager man;

    Stock st = man.getStock("AA");
    std::cout << "Hellow" << std::endl;
    return 0;
}