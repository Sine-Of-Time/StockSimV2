// user.cpp
#include "user.h"

// Constructor
User::User(const std::string& username, int networth) : username(username), networth(networth) {}

// Getters
std::string User::getUsername() const {
    return username;
}

int User::getNetworth() const {
    return networth;
}

// Setters
void User::setUsername(const std::string& username) {
    this->username = username;
}

void User::setNetworth(int networth) {
    this->networth = networth;
}

// Placeholder functions
void User::buyStock() {
    // To be implemented
}

void User::sellStock() {
    // To be implemented
}
