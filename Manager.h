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

public:
    // Constructor
    Manager();

    // Main functions
    std::vector<std::string> initStock(const std::string tckr) const;
    void displayLine();
    void miscMenu();
    void displayMainMenu();
    void createUser();
    void searchForStock();
    User findUserByUsername(const std::string& userName) const;
    void saveUserData(const User& user, const std::string& filename) const;
    void displayLogin();
    void wipeFileData(const std::string& filename) const;
    void saveUsers(const std::string& filename) const;
    void loadUsers(const std::string& filename);
    User loadUserData(const std::string& filename) const;
    const std::vector<User>& getUsers() const;
    void setUsers(const std::vector<User>& newUsers);

    // User Management
    void addUser(const User& user);            // Add a new user
    bool removeUser(const std::string& username); // Remove a user by username
    User getUserByIndex(size_t index) const;      // Get a user by index

    // Getters
    Stock getStock(const std::string tckr) const;

    // Setters
    void setStockErrorTicker(bool status);

    // Destructor
    ~Manager();
};

#endif // MANAGER_H

