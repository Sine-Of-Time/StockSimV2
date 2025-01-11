#include <iostream>
#include <curl/curl.h>
#include <json/json.h> // Include JSONCPP header
#include "curl_function.h"


using namespace std;

int main() {
    std::string ticker_symbol = "AA"; // Example ticker symbol
    std::string api_key = "2c53720136914f2e9a7c3623f965eb14";
    Json::Value stockData = get_stock_quote(ticker_symbol, api_key);

    if (!stockData.isNull()) {
        // Extract variables from the JSON object
        string companyName = stockData.get("name", "Unknown").asString();
        string volume = stockData.get("average_volume", 0).asString();
        string ticker = stockData.get("symbol", "Unknown").asString();
        int64_t timestamp = stockData.get("timestamp", "Unknown").asInt64();
        string  value = stockData.get("open", 0.0).asString();
        string  change = stockData.get("change", 0.0).asString();
        string  previousClose = stockData.get("previous_close", 0.0).asString();

        // Print the extracted variables
        std::cout << "Stock Data for " << ticker_symbol << ":\n";
        std::cout << "Company Name: " << companyName << "\n";
        std::cout << "Ticker: " << ticker << "\n";
        std::cout << "Timestamp: " << timestamp << "\n";
        std::cout << "Value: " << value << "\n";
        std::cout << "Change: " << change << "\n";
        std::cout << "Previous Close: " << previousClose << "\n";
        std::cout << "Volume: " << volume << "\n";
    }
    else {
        std::cerr << "Failed to retrieve stock data." << std::endl;
    }

    return 0;
}
