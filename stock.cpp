#include "stock.h"
#include "curl_function.h"
#include <vector>
#include <iostream> // For std::cout and std::endl
//using namespace std;

// Constructor
Stock::Stock(const std::string& volume, const std::string& companyName, const std::string& ticker,
    int64_t timestamp, const std::string& value, const std::string& change,
    const std::string& previousClose, bool up)
    : volume(volume), companyName(companyName), ticker(ticker), timestamp(timestamp),
    value(value), change(change), previousClose(previousClose), up(up) {
        getHistory();
    }

// Display data
void Stock::displayData() {
    std::cout << "Company Name: " << companyName << std::endl;
    std::cout << "Ticker: " << ticker << std::endl;
    std::cout << "Timestamp: " << timestamp << std::endl;
    std::cout << "Value: " << value << std::endl;
    std::cout << "Change: " << change << std::endl;
    std::cout << "Previous Close: " << previousClose << std::endl;
    std::cout << "Volume: " << volume << std::endl;
    std::cout << "Direction: " << (up ? "Up" : "Down") << std::endl;
}

// Getters
std::string Stock::getVolume() const {
    return volume;
}

std::string Stock::getCompanyName() const {
    return companyName;
}

std::string Stock::getTicker() const {
    return ticker;
}

int64_t Stock::getTimestamp() const {
    return timestamp;
}

std::string Stock::getValue() const {
    return value;
}

std::string Stock::getChange() const {
    return change;
}

std::string Stock::getPreviousClose() const {
    return previousClose;
}

void Stock::getHistory() {
    history = get_stock_prices(ticker);
}

// Setters
void Stock::setVolume(const std::string& newVolume) {
    volume = newVolume;
}

void Stock::setCompanyName(const std::string& newCompanyName) {
    companyName = newCompanyName;
}

void Stock::setTicker(const std::string& newTicker) {
    ticker = newTicker;
}

void Stock::setTimestamp(int64_t newTimestamp) {
    timestamp = newTimestamp;
}

void Stock::setValue(const std::string& newValue) {
    value = newValue;
}

void Stock::setChange(const std::string& newChange) {
    change = newChange;
}

void Stock::setPreviousClose(const std::string& newPreviousClose) {
    previousClose = newPreviousClose;
}
