#include "Manager.h"
#include "stock.h"
#include "curl_function.h"
#include <cstring> // For std::memcpy
#include <curl/curl.h>
#include <json/json.h> // Include JSONCPP header
#include <string>
#include <vector>
#include <iostream>
#include <algorithm>

// Constructor
Manager::Manager() {
   
}

Stock Manager::getStock(const std::string ticker) const {
    std::vector<std::string> tmpStorage = initStock(ticker);
    Json::Value stockData = get_stock_quote(ticker);
    Stock newStock( // Create a Stock object and push it to the stock stack
        tmpStorage[1],                  // Name
        tmpStorage[0],                  // Average Volume
        tmpStorage[2],                  // Symbol
        stockData.get("timestamp", 0).asInt64(), // Timestamp
        tmpStorage[3],                  // Open
        tmpStorage[4],                  // Change
        tmpStorage[5],                  // Previous Close
        false                           // Assume false for additional flag
    );
    return newStock;
}

std::vector<std::string> Manager::initStock(const std::string ticker) const {
    std::string api_key = "2c53720136914f2e9a7c3623f965eb14";
    Json::Value stockData = get_stock_quote(ticker);
    std::vector<std::string> tmpStorage;

    if (!((stockData.get("name", "Unknown").asString()).compare("Unknown"))) {
        std::cout << "Could not find stock with ticker:" << ticker << std::endl;
        tmpStorage = { "Error", "Error", "Error", "Error", "Error", "Error" };
        return tmpStorage;
    }std::string keys[] = { "name", "average_volume", "symbol", "open", "change", "previous_close" };   // Define an array of keys to extract data

    // Extract data into tmpStorage
    for (int i = 0; i < 6; i++) {
        tmpStorage.push_back(stockData.get(keys[i], "Unknown").asString());
        //tmpStorage[i] = stockData.get(keys[i], "Unknown").asString();
    }return tmpStorage;
}

// Destructor
Manager::~Manager() {}

