#ifndef HEADER_GUARD_H
#define HEADER_GUARD_H

#pragma once

#include <string>
#include <json/json.h>
//using namespace std;

// Declare functions 
std::string get_price(const std::string& ticker_symbol, const std::string& api);
Json::Value get_stock_quote(const std::string & ticker_symbol);
std::vector<double> get_stock_prices(const std::string& ticker_symbol);
std::string fetchTwelveData(const std::string& url);
std::vector<std::string> searchStocksByPrefix(const std::string& prefix, const std::string& apiKey);

#endif // HEADER_GUARD_H
