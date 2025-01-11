#ifndef COMPANY_H
#define COMPANY_H

#include <string>
#include <unordered_map>
#include "stock.h"

class Company {
private:
    std::string companyName;
    std::string ticker;
    std::unordered_map<std::string,Stock> stockMap;// Array to store stock volume percentages

public:
    // Constructor
    Company(const std::string& name = "", const std::string& tickerSymbol = "", const std::unordered_map<std::string, Stock>& stocks = {});

    void initStocks(const std::string& ticker_symbol);

    // Getters
    std::string getCompanyName() const;
    std::string getTicker() const;


    // Setters
    void setCompanyName(const std::string& name);
    void setTicker(const std::string& tickerSymbol);


    // Destructor
    ~Company();
};

#endif // COMPANY_H