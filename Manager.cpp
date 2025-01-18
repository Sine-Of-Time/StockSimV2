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


void Manager::searchForStock() {
    std::string userPrefix;

    while (true) {
        std::cout << "Enter stock symbol prefix (or 'exit' to quit): ";
        std::cin >> userPrefix;

        if (userPrefix == "exit") {
            break;
        }

        // Fetch matching stock symbols
        std::vector<std::string> matches = searchStocksByPrefix(userPrefix, "2c53720136914f2e9a7c3623f965eb14");

        if (matches.empty()) {
            std::cout << "No matches found for prefix '" << userPrefix << "'." << std::endl;
        }
        else {
            std::cout << "Suggestions: ";
            int k = 0;
            setStockErrorTicker(false);
            for (const auto& symbol : matches) {
                Stock st = getStock(symbol);
                if (st.getCompanyName().compare("Error") != 0) {
                    st.displayData();
                    displayLine();
                }
                if (k++ == 5)break;
            }
            std::cout << std::endl;
        }
    }
    setStockErrorTicker(true);
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
        if(showStockErrorTicker)std::cout << "Could not find stock with ticker:" << ticker << std::endl;
        tmpStorage = { "Error", "Error", "Error", "Error", "Error", "Error" };
        return tmpStorage;
    }std::string keys[] = { "name", "average_volume", "symbol", "open", "change", "previous_close" };   // Define an array of keys to extract data

    // Extract data into tmpStorage
    for (int i = 0; i < 6; i++) {
        tmpStorage.push_back(stockData.get(keys[i], "Unknown").asString());
    }return tmpStorage;
}

void Manager::displayLine() {
    std::cout << "----------------------------------------------------------\n";
}

void Manager::displayMainMenu() {
    std::cout << "\n=== StockSim Menu ===\n";
    std::cout << "1. Search for Stocks\n";
    std::cout << "2. View your Portfolio\n";
    std::cout << "3. View your Info\n";
    std::cout << "4. Exit\n";
    std::cout << "Enter your choice: ";
}

void Manager::setStockErrorTicker(bool status) {
    showStockErrorTicker = status;
}

// Destructor
Manager::~Manager() {}
