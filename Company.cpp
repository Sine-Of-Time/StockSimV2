#include "Company.h"
#include "stock.h"
#include "curl_function.h"
#include <cstring> // For std::memcpy
#include <curl/curl.h>
#include <json/json.h> // Include JSONCPP header
#include <unordered_map>

//using namespace std;
// Constructor
Company::Company(const std::string& name, const std::string& tickerSymbol, const std::unordered_map<std::string, Stock>& stockMap)
    : companyName(name), ticker(tickerSymbol) {
   
}

// Getters
std::string Company::getCompanyName() const {
    return companyName;
}

std::string Company::getTicker() const {
    return ticker;
}


// Setters
void Company::setCompanyName(const std::string& name) {
    companyName = name;
}

void Company::setTicker(const std::string& tickerSymbol) {
    ticker = tickerSymbol;
}


//There are some potential issues with this worth looking into -1/11/25
void Company::initStocks(const std::string& ticker_symbol) {
    std::string api_key = "2c53720136914f2e9a7c3623f965eb14";
    Json::Value stockData = get_stock_quote(ticker_symbol, api_key);

    // Define an array of keys to extract data
    std::string keys[] = { "name", "average_volume", "symbol", "open", "change", "previous_close" };
    std::string tmpStorage[6];

    // Extract data into tmpStorage
    for (int i = 0; i < 6; i++) {
        tmpStorage[i] = stockData.get(keys[i], "Unknown").asString();
    }

    // Create a Stock object and add it to stockMap
    Stock stock(
        tmpStorage[0],                  // Name
        tmpStorage[1],                  // Average Volume
        tmpStorage[2],                  // Symbol
        stockData.get("timestamp", 0).asInt64(), // Timestamp
        tmpStorage[3],                  // Open
        tmpStorage[4],                  // Change
        tmpStorage[5],                  // Previous Close
        false                           // Assume false for additional flag
    );

    // Use symbol (tmpStorage[2]) as the key in stockMap
    stockMap[tmpStorage[2]] = stock;
}

// Destructor
Company::~Company() {}

