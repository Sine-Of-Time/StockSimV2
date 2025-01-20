#ifndef MANAGER_H
#define MANAGER_H

#include <string>
#include <unordered_map>
#include "stock.h"
#include <vector>
#include "user.h"

class Manager {
private:
    std::vector<User> users;
    bool showStockErrorTicker;
    bool debug = false;
    
    //Private functions
    double roundToPrecision(double value, int precision) const;

public:
    // Constructor
    Manager();

    // Main functions
    std::vector<std::string> initStock(const std::string tckr) const;
    void displayLine();
    void displayLogin();
    void displayMainMenu();
    void miscMenu();
    void createUser();
    void searchForStock();
    User findUserByUsername(const std::string& userName) const;
    void saveUserData(const User& user, const std::string& filename) const;
    void wipeFileData(const std::string& filename) const;
    void saveUsers(const std::string& filename) const;
    void loadUsers(const std::string& filename);
    User loadUserData(const std::string& filename) const;

    // User Management
    void addUser(const User& user);            // Add a new user
    bool removeUser(const std::string& username); // Remove a user by username
    User getUserByIndex(size_t index) const;      // Get a user by index

    // Getters
    Stock getStock(const std::string tckr) const;
    const std::vector<User>& getUsers() const;

    // Setters
    void setStockErrorTicker(bool status);
    void setUsers(const std::vector<User>& newUsers);

    // Destructor
    ~Manager();
};
#endif // MANAGER_H