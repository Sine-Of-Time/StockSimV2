#ifndef STOCK_H
#define STOCK_H

#include <string>
#include <vector>
#include <cstdint>

class Stock {
private:
    double volume;
    std::string companyName;
    std::string ticker;
    int64_t timestamp;
    double value;
    std::string change;
    std::string previousClose;
    std::vector<double> history;
    int issuedQuantity;
    bool up;
    //Private functions
    void setHistory();

public:
    // Constructor
    Stock(double volume = 0.0,
        const std::string& companyName = "",
        const std::string& ticker = "",
        int64_t timestamp = 0,
        double value = 0.0,
        const std::string& change = "0.0",
        const std::string& previousClose = "0.0",
        bool up = false,
        int issuedQuantity = 0);

    void increaseIssuedQuantityBy(int increase);
    void decreaseIssuedQuantityBy(int decrease);
    void bestTimeToBuyLast30Days();

    // Getters
    double getVolume() const;
    std::string getCompanyName() const;
    std::string getTicker() const;
    int64_t getTimestamp() const;
    double getValue() const;
    std::string getChange() const;
    std::string getPreviousClose() const;
    std::vector<double> getHistory() const;
    int getIssuedQuantity() const;

    // Setters
    void setVolume(double newVolume);
    void setCompanyName(const std::string& newCompanyName);
    void setTicker(const std::string& newTicker);
    void setTimestamp(int64_t newTimestamp);
    void setValue(double newValue);
    void setChange(const std::string& newChange);
    void setPreviousClose(const std::string& newPreviousClose);
    void setIssuedQuantity(int newIssuedQuantity);

    // Functions to display stock data
    void displayData();
    void displayGraph();

    // Destructor
    virtual ~Stock() {}
};

#endif // STOCK_H
