#include "curl_function.h"
#include <curl/curl.h>
#include <string>
#include <vector>
#include <iostream>
//#include <iostream>

using namespace Json;
using namespace std;


std::string api = "2c53720136914f2e9a7c3623f965eb14";

// Callback function for cURL to handle the response
size_t WriteCallback(void* contents, size_t size, size_t nmemb, string* output) {
    size_t totalSize = size * nmemb;
    output->append(static_cast<char*>(contents), totalSize);
    return totalSize;
}

string get_price(const string& ticker_symbol, const string& api) {
    CURL* curl = curl_easy_init();
    if (!curl) {
        cerr << "Failed to initialize cURL." << endl;
        return "";
    }

    // Set up the URL
    string url = "https://api.twelvedata.com/price?symbol=" + ticker_symbol + "&apikey=" + api;
    curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);

    // Create a string to store the JSON response
    string jsonResponse;

    curl_easy_setopt(curl, CURLOPT_WRITEDATA, &jsonResponse);

    // Perform the HTTP request
    CURLcode res = curl_easy_perform(curl);
    if (res != CURLE_OK) {
        cerr << "cURL request failed: " << curl_easy_strerror(res) << endl;
        return "";
    }

    // Clean up cURL
    curl_easy_cleanup(curl);

    // Parse the JSON data using JsonCpp
    CharReaderBuilder builder;
    CharReader* reader = builder.newCharReader();
    Value root;
    string errors;
    if (!reader->parse(jsonResponse.c_str(), jsonResponse.c_str() + jsonResponse.size(), &root, &errors)) {
        cerr << "Failed to parse JSON: " << errors << endl;
        delete reader;
        return "";
    }
    delete reader;

    // Extract and return the price
    string price = root["price"].asString();
    return price;
}

Value get_stock_quote(const std::string& ticker_symbol) {
    CURL* curl = curl_easy_init();
    if (!curl) {
        cerr << "Failed to initialize cURL." << endl;
        return Value(); // Return an empty JSON value on error
    }

    // Set up the URL
    string url = "https://api.twelvedata.com/quote?symbol=" + ticker_symbol + "&apikey=" + api;
    curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);

    // Create a string to store the JSON response
    string jsonResponse;

    curl_easy_setopt(curl, CURLOPT_WRITEDATA, &jsonResponse);

    // Perform the HTTP request
    CURLcode res = curl_easy_perform(curl);
    if (res != CURLE_OK) {
        cerr << "cURL request failed: " << curl_easy_strerror(res) << endl;
        return Value(); // Return an empty JSON value on error
    }

    // Clean up cURL
    curl_easy_cleanup(curl);

    // Parse the JSON data using JsonCpp
    CharReaderBuilder builder;
    CharReader* reader = builder.newCharReader();
    Value root;
    string errors;
    if (!reader->parse(jsonResponse.c_str(), jsonResponse.c_str() + jsonResponse.size(), &root, &errors)) {
        cerr << "Failed to parse JSON: " << errors << endl;
        delete reader;
        return Value(); // Return an empty JSON value on error
    }
    delete reader;

    return root;
}

//This works -11/12/24
std::vector<double> get_stock_prices(const std::string& ticker_symbol) {
    CURL* curl = curl_easy_init();
    if (!curl) {
        std::cout << "Failed to initialize cURL." << std::endl;
        return {}; // Return an empty vector on error
    }

    // Set up the URL
    std::string url = "https://api.twelvedata.com/time_series?symbol=" + ticker_symbol +
        "&interval=1day&outputsize=30&apikey=" + api;
    curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);

    // Create a string to store the JSON response
    std::string jsonResponse;
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, &jsonResponse);

    // Perform the HTTP request
    CURLcode res = curl_easy_perform(curl);
    if (res != CURLE_OK) {
        //std::cerr << "cURL request failed: " << curl_easy_strerror(res) << std::endl;
        curl_easy_cleanup(curl);
        return {}; // Return an empty vector on error
    }

    // Clean up cURL
    curl_easy_cleanup(curl);

    // Parse the JSON response
    Json::CharReaderBuilder reader;
    Json::Value jsonData;
    std::string errs;

    std::istringstream sstream(jsonResponse);
    if (!Json::parseFromStream(reader, sstream, &jsonData, &errs)) {
        //std::cerr << "Failed to parse JSON: " << errs << std::endl;
        return {}; // Return an empty vector on error
    }

    // Extract closing prices and store them in a vector
    std::vector<double> closingPrices;
    for (const auto& day : jsonData["values"]) {
        double close = std::stod(day["close"].asString());
        closingPrices.push_back(close);
    }

    return closingPrices; // Return the vector of closing prices
}