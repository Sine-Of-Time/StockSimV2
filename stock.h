#ifndef STOCK_H
#define STOCK_H

#include <string>
#include <vector>
//using namespace std;

class Stock {
private:
    std::string volume;
    std::string companyName;
    std::string ticker;
    int64_t timestamp;
    std::string value;
    std::string change;
    std::string previousClose;
    std::vector<double> history;
    bool up;
    int issuedQuantity; // New data member

    void setHistory();

public:
    // Constructor
    Stock(const std::string& volume = "",
        const std::string& companyName = "",
        const std::string& ticker = "",
        int64_t timestamp = 0,
        const std::string& value = "0.0",
        const std::string& change = "0.0",
        const std::string& previousClose = "0.0",
        bool up = false,
        int issuedQuantity = 0); // Updated constructor

    void increaseIssuedQuantityBy(int increase);
    void decreaseIssuedQuantityBy(int decrease);

    // Getters
    std::string getVolume() const;
    std::string getCompanyName() const;
    std::string getTicker() const;
    int64_t getTimestamp() const;
    std::string getValue() const;
    std::string getChange() const;
    std::string getPreviousClose() const;
    std::vector<double> getHistory();
    int getIssuedQuantity() const; // New getter

    // Setters
    void setVolume(const std::string& newVolume);
    void setCompanyName(const std::string& newCompanyName);
    void setTicker(const std::string& newTicker);
    void setTimestamp(int64_t timestamp);
    void setValue(const std::string& newValue);
    void setChange(const std::string& newChange);
    void setPreviousClose(const std::string& newPreviousClose);
    void setIssuedQuantity(int newIssuedQuantity); // New setter

    // Display data
    void displayData();
    void displayGraph();

    // Virtual destructor
    virtual ~Stock() {}
};

#endif // STOCK_H
