#ifndef HEADER_GUARD_H
#define HEADER_GUARD_H

#pragma once

#include <string>
#include <json/json.h>
//using namespace std;

// Declare functions 
std::string get_price(const std::string& ticker_symbol, const std::string& api);

Json::Value get_stock_quote(const std::string & ticker_symbol, const std::string & api);

#endif // HEADER_GUARD_H
