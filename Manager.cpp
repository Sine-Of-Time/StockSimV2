#include "Manager.h"
#include "stock.h"
#include "curl_function.h"
#include <cstring> // For std::memcpy
#include <curl/curl.h>
#include <json/json.h> // Include JSONCPP header
#include <unordered_map>
#include <stack>
#include <iostream>

// Constructor
Manager::Manager() {
    
     
}

Stock Manager::getStock(const std::string ticker) const {
    return initStock(ticker);
}

Stock Manager::initStock(const std::string ticker) const {
    std::string api_key = "2c53720136914f2e9a7c3623f965eb14";
    Json::Value stockData = get_stock_quote(ticker);

    if (!((stockData.get("name", "Unknown").asString()).compare("Unknown"))) {
        std::cout << "Could not find stock with ticker:" << ticker << std::endl;
        Stock stock;
        return stock;
    }
    // Define an array of keys to extract data
    std::string keys[] = { "name", "average_volume", "symbol", "open", "change", "previous_close" };
    std::string tmpStorage[6];

    // Extract data into tmpStorage
    for (int i = 0; i < 6; i++) {
        tmpStorage[i] = stockData.get(keys[i], "Unknown").asString();
    }


    
    // Create a Stock object and push it to the stock stack
    Stock newStock(
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

// Destructor
Manager::~Manager() {}

