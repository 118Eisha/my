#pragma once
#include <string>
using namespace std;

class Admin {
public:
    Admin();
    ~Admin();

    // Login with debug info and case-insensitive name check
    bool login(const string& username, const string& password) const;

private:
    string admin_username;
    string admin_password_hash;
};