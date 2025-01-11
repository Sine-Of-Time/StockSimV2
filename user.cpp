// user.h
#ifndef USER_H
#define USER_H

#include <string>
#include <unordered_map>

class User {
private:
    std::string username;
    //std::unordered_map<std::string, Stock> portfolio;
    int networth;

public:
    // Constructor
    User(const std::string& username = "", int networth = 0);

    // Getters
    std::string getUsername() const;
    int getNetworth() const;

    // Setters
    void setUsername(const std::string& username);
    void setNetworth(int networth);

    // Placeholder functions
    void buyStock();
    void sellStock();
};

#endif // USER_H
