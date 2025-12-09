#include "admin.h"
#include "utils.h"
#include <iostream>

Admin::Admin() {
    // Default admin login (update as needed!)
    admin_username = "Eisha";
    admin_password_hash = simple_hash("2244"); // default password: "1234"
}

Admin::~Admin() {}

bool Admin::login(const string& username, const string& password) const {
    // Case-insensitive username match and debug info
    std::string input_name = username;
    std::string input_pass = password;

    // Debug output for troubleshooting
    std::cout << "[DEBUG] Input username: '" << input_name << "'\n";
    std::cout << "[DEBUG] Expected username: '" << admin_username << "'\n";
    std::cout << "[DEBUG] Input password: '" << input_pass << "'\n";
    std::cout << "[DEBUG] hash(input): '" << simple_hash(input_pass) << "'\n";
    std::cout << "[DEBUG] stored hash: '" << admin_password_hash << "'\n";

    bool user_match = toLower(input_name) == toLower(admin_username);
    bool pass_match = simple_hash(input_pass) == admin_password_hash;

    return user_match && pass_match;
}