#ifndef STOCK_H
#define STOCK_H

#include <string>
using namespace std;

class Stock {
private:
    std::string volume;
    std::string companyName;
    std::string ticker;
    int64_t timestamp;
    std::string value;
    std::string change;
    std::string previousClose;
    double history[30];
    bool up;

public:
    // Constructor
    Stock(const std::string& volume = "",
        const std::string& companyName = "",
        const std::string& ticker = "",
        int64_t timestamp = 0,
        const std::string& value = "0.0",
        const std::string& change = "0.0",
        const std::string& previousClose = "0.0",
        bool up = false);

    // Getters
    std::string getVolume() const;
    std::string getCompanyName() const;
    std::string getTicker() const;
    int64_t getTimestamp() const;
    std::string getValue() const;
    std::string getChange() const;
    std::string getPreviousClose() const;

    // Setters
    void setVolume(const std::string& newVolume);
    void setCompanyName(const std::string& newCompanyName);
    void setTicker(const std::string& newTicker);
    void setTimestamp(int64_t timestamp);
    void setValue(const std::string& newValue);
    void setChange(const std::string& newChange);
    void setPreviousClose(const std::string& newPreviousClose);

    // Pure virtual function for update (to be implemented by derived classes)
   // virtual void update() = 0;

    // Display data
    void displayData();

    // Virtual destructor
    virtual ~Stock() {}
};

#endif // STOCK_H
