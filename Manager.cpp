#define API_KEY "2c53720136914f2e9a7c3623f965eb14"

#include "Manager.h"
#include "stock.h"
#include "curl_function.h"
#include <cstring> 
#include <curl/curl.h>
#include <json/json.h>
#include <string>
#include <vector>
#include <iostream>
#include <algorithm>
#include <fstream>
#include "user.h"
#include <list>

// Constructor
Manager::Manager() {
   
}

void Manager::displayLogin() {
    std::cout << "\n=== StockSim Login ===\n";
    std::cout << "1.Login into existing account\n";
    std::cout << "2.Create new user\n";
}

void Manager::createUser() {
    std::string tmpUserName;
    double tmpBalance;
    std::cout << "Please enter the new users name:\n";
    std::cin >> tmpUserName;
    std::cout << "Please enter the new users balance\n";
    std::cin >> tmpBalance;
    User tmpUser(tmpUserName, tmpBalance);
    addUser(tmpUser);
}

User Manager::findUserByUsername(const std::string& userName) const {
    // Iterate through the users array to find a match
    for (const auto& user : users) {
        if (user.getUsername() == userName)return user;
    }

    // If no match is found, return a default User object
    std::cerr << "User with username \"" << userName << "\" not found.\n";
    return User(); // Default user
}

void Manager::wipeFileData(const std::string& filename) const {
    std::ofstream outFile(filename, std::ios::out | std::ios::trunc); // Open in truncate mode
    if (!outFile) {
        std::cerr << "Error: Unable to open file " << filename << " for writing.\n";
        return;
    }

    // File is now empty
    outFile.close();
    std::cout << "File " << filename << " has been wiped clean.\n";
}

void Manager::saveUsers(const std::string& filename) const {
    std::ofstream outFile(filename, std::ios::out | std::ios::trunc); // Overwrite the file
    if (!outFile) {
        std::cerr << "Error: Unable to open file " << filename << " for writing.\n";
        return;
    }

    // Write the number of users
    outFile << users.size() << "\n";

    // Write each user's data
    for (const auto& user : users) {
        outFile << user.getUsername() << "\n";
        outFile << user.getBalance() << "\n";
        outFile << user.getNetworth() << "\n";

        const auto& portfolio = user.getPortfolio();
        outFile << portfolio.size() << "\n"; // Number of stocks in the portfolio
        for (const auto& [ticker, stock] : portfolio) {
            outFile << stock.getCompanyName() << "\n";
            outFile << stock.getTicker() << "\n";
            outFile << stock.getValue() << "\n";
            outFile << stock.getIssuedQuantity() << "\n";
        }
    }

    outFile.flush(); // Ensure all data is written to the file
    outFile.close();
    if (outFile.fail()) std::cerr << "Error: Failed to properly save data to " << filename << ".\n";
    else std::cout << "All users' data saved to " << filename << ".\n";
}


void Manager::loadUsers(const std::string& filename) {
    std::ifstream inFile(filename);
    if (!inFile) {
        std::cerr << "Error: Unable to open file " << filename << " for reading.\n";
        return;
    }

    size_t userCount;
    inFile >> userCount;
    inFile.ignore(); // Ignore the newline after userCount

    users.clear(); // Clear the existing users array

    for (size_t i = 0; i < userCount; ++i) {
        std::string username;
        int balance, networth;
        size_t portfolioSize;

        std::getline(inFile, username);
        inFile >> balance >> networth >> portfolioSize;
        inFile.ignore(); // Ignore the newline after portfolioSize

        User user(username, networth);
        user.setBalance(balance);

        for (size_t j = 0; j < portfolioSize; ++j) {
            std::string companyName, ticker, valueStr;
            int issuedQuantity;

            std::getline(inFile, companyName);
            std::getline(inFile, ticker);
            std::getline(inFile, valueStr);
            inFile >> issuedQuantity;
            inFile.ignore(); // Ignore the newline after issuedQuantity

            // Convert value to double
            double value = std::stod(valueStr);

            // Create Stock object with default or placeholder values for missing fields
            Stock stock(0.0,          // Volume (default)
                companyName,  // Company Name
                ticker,       // Ticker
                0,            // Timestamp (default)
                value,        // Value
                "0.0",        // Change (default)
                "0.0",        // Previous Close (default)
                false,        // Up (default)
                issuedQuantity); // Issued Quantity

            user.addStock(stock);
        }

        users.push_back(user);
    }

    inFile.close();
    std::cout << "All users' data loaded from " << filename << ".\n";
}


void Manager::saveUserData(const User& user, const std::string& filename) const {
    std::ofstream outFile(filename, std::ios::out | std::ios::trunc); // Overwrite the file
    if (!outFile) {
        std::cerr << "Error: Unable to open file " << filename << " for writing.\n";
        return;
    }

    // Write user data
    outFile << user.getUsername() << "\n";
    outFile << user.getBalance() << "\n";
    outFile << user.getNetworth() << "\n";

    // Write portfolio data
    const auto& portfolio = user.getPortfolio(); 
    outFile << portfolio.size() << "\n"; // Number of stocks in the portfolio
    for (const auto& [ticker, stock] : portfolio) {
        outFile << stock.getCompanyName() << "\n";
        outFile << stock.getTicker() << "\n";
        outFile << stock.getValue() << "\n";
        outFile << stock.getIssuedQuantity() << "\n";
    }

    outFile.close();
    std::cout << "User data saved to " << filename << ".\n";
}

User Manager::loadUserData(const std::string& filename) const {
    std::ifstream inFile(filename);
    if (!inFile) {
        std::cerr << "Error: Unable to open file " << filename << " for reading.\n";
        return User(); // Return a default `User` object
    }

    std::string username;
    int balance, networth;
    size_t portfolioSize;

    // Read user data
    std::getline(inFile, username);
    inFile >> balance >> networth >> portfolioSize;
    inFile.ignore(); // Ignore the newline after portfolioSize

    User user(username, networth);
    user.setBalance(balance);

    // Read portfolio data
    for (size_t i = 0; i < portfolioSize; ++i) {
        std::string companyName, ticker, valueStr;
        int issuedQuantity;

        std::getline(inFile, companyName);
        std::getline(inFile, ticker);
        std::getline(inFile, valueStr);
        inFile >> issuedQuantity;
        inFile.ignore(); // Ignore the newline after issuedQuantity

        // Convert string value to double
        double value = std::stod(valueStr);

        // Create Stock object with default or placeholder values for missing fields
        Stock stock(0.0, companyName, ticker, 0, value, "0.0", "0.0", false, issuedQuantity);

        user.buyStock(stock, issuedQuantity); // Add the stock to the user's portfolio
    }inFile.close();
  
    std::cout << "User data loaded from " << filename << ".\n";
    return user;
}

void Manager::miscMenu() {
    std::cout << "\n=== Misc Menu ===\n";
    std::cout << "1. Best Time To Buy Stock Last 30 Days\n";
    std::cout << "2. Exit\n";
    std::cout << "Enter your choice: ";
}

void Manager::addUser(const User& user) {
    // Check if the user already exists
    auto it = std::find_if(users.begin(), users.end(),
        [&user](const User& u) { return u.getUsername() == user.getUsername(); });

    if (it != users.end()) {
        // Update the existing user with the new user's details
        *it = user; // Assuming operator= is implemented for User
        std::cout << "User " << user.getUsername() << " updated successfully.\n";
        return;
    }

    // Add the new user
    users.push_back(user);
    std::cout << "User " << user.getUsername() << " added successfully.\n";
}
// Remove a user by username
bool Manager::removeUser(const std::string& username) {
    auto it = std::remove_if(users.begin(), users.end(),
        [&username](const User& u) { return u.getUsername() == username; });

    if (it == users.end()) {
        std::cout << "User " << username << " not found.\n";
        return false; // User not found
    }

    users.erase(it, users.end()); // Remove user(s)
    std::cout << "User " << username << " removed successfully.\n";
    return true;
}

void Manager::searchForStock() {
    std::string userPrefix;

    while (true) {
        std::cout << "Would you like to search for an stock?(exit move on): ";
        std::cin >> userPrefix;

        if (userPrefix == "exit") break;

        // Fetch matching stock symbols
        std::vector<std::string> matches = searchStocksByPrefix(userPrefix, API_KEY);

        if (matches.empty()) std::cout << "No matches found for prefix '" << userPrefix << "'." << std::endl;
        else{
            std::cout << "Suggestions: ";
            int k = 0;
            
            setStockErrorTicker(false);
            std::list<std::string> usedTickerList;
            for (const auto& symbol : matches) {
                Stock st = getStock(symbol);
            
                auto it = std::find(usedTickerList.begin(), usedTickerList.end(),symbol);
                if (it != usedTickerList.end()) continue;

                if (st.getVolume() == 0.0)continue;
                if (st.getCompanyName().compare("Error") != 0 || st.getCompanyName().compare("") != 0) {
                    st.displayData();
                    displayLine();
                }
                usedTickerList.push_back(st.getTicker());
                if (k++ == 10)break;
            }std::cout << std::endl;
        }
    }setStockErrorTicker(true);
}

Stock Manager::getStock(const std::string ticker) const {
    std::vector<std::string> tmpStorage = initStock(ticker);
    Json::Value stockData = get_stock_quote(ticker);

    if (tmpStorage[1].compare("Error") == 0)return Stock();
    double tmpVolume = std::stod(tmpStorage[1]);
    double tmpOpen = std::stod(tmpStorage[3]);
    tmpVolume = roundToPrecision(tmpVolume, 2);
    tmpOpen = roundToPrecision(tmpOpen, 2);

    std::string companyName = tmpStorage[0];
    std::string change = tmpStorage[4];
    std::string previousClose = tmpStorage[5];

    Stock newStock(tmpVolume,// Volume
        companyName,         // Company Name
        tmpStorage[2],       // Ticker
        stockData.get("timestamp", 0).asInt64(), // Timestamp
        tmpOpen,             // Open/Value
        change,              // Change
        previousClose,       // Previous Close
        false,               // Up
        0);                  // Issued Quantity (default)
    return newStock;
}

User Manager::getUserByIndex(size_t index) const {
    if (index >= users.size()) throw std::out_of_range("Index is out of bounds.");
    return users[index];
}

const std::vector<User>& Manager::getUsers() const {
    return users;
}

std::vector<std::string> Manager::initStock(const std::string ticker) const {
    // double value = std::stod(str); // Convert the string to a double
    std::string api_key = API_KEY;
    Json::Value stockData = get_stock_quote(ticker);
    std::vector<std::string> tmpStorage;

    std::string tmpStr2= stockData.get("name", "Unknown").asString();
    if (!(tmpStr2.compare("Unknown"))) {
        if(showStockErrorTicker)std::cout << "Could not find stock with ticker:" << ticker << std::endl;
        tmpStorage = { "Error", "Error", "Error", "Error", "Error", "Error" };
        return tmpStorage;
    }std::string keys[] = { "name", "average_volume", "symbol", "open", "change", "previous_close" };   // Define an array of keys to extract data

    // Extract data into tmpStorage
    for (int i = 0; i < 6; i++) {
        Json::Value valueTmp = stockData.get(keys[i], "Unknown");
        if (keys[i].compare("average_volume") == 0 || keys[i].compare("previous_close")== 0 || keys[i].compare("open") == 0) {
            std::string tmpString = valueTmp.asString();
            double tmpDouble = std::stod(tmpString);
            tmpDouble = roundToPrecision(tmpDouble,2);
            tmpString = std::to_string(tmpDouble);

            tmpStorage.push_back(tmpString);
        }else tmpStorage.push_back(valueTmp.asString());
    }return tmpStorage;
}

double Manager::roundToPrecision(double value, int precision) const {
    double scale = std::pow(10.0, precision);
    return std::round(value * scale) / scale;
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

void Manager::setUsers(const std::vector<User>& newUsers) {
    users = newUsers;
}

// Destructor
Manager::~Manager() {}