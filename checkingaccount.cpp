#include "checkingaccount.h"
#include <iostream>
#include <sstream>

CheckingAccount::CheckingAccount() : BankAccount(), overdraft_limit(100.0) {}

CheckingAccount::CheckingAccount(const string& account_number, const string& owner_name, const string& password_hash, double balance, double overdraft_limit)
    : BankAccount(account_number, owner_name, password_hash, balance), overdraft_limit(overdraft_limit) {}

CheckingAccount::~CheckingAccount() {}

bool CheckingAccount::withdraw(double amount) {
    if (amount <= balance + overdraft_limit) {
        balance -= amount;
        cout << "Withdrew $" << amount << " from account " << account_number << endl;
        return true;
    } else {
        cout << "Overdraft limit exceeded for account " << account_number << endl;
        return false;
    }
}

string CheckingAccount::toCSV() const {
    stringstream ss;
    ss << account_number << "," << owner_name << "," << password_hash << "," << balance << "," << overdraft_limit;
    return ss.str();
}

void CheckingAccount::fromCSV(const string& line) {
    stringstream ss(line);
    string bal_str, overdraft_str;
    getline(ss, account_number, ',');
    getline(ss, owner_name, ',');
    getline(ss, password_hash, ',');
    getline(ss, bal_str, ',');
    getline(ss, overdraft_str, ',');
    balance = stod(bal_str);
    overdraft_limit = stod(overdraft_str);
}

void CheckingAccount::displayInfo() const {
    cout << "Checking Account\n";
    BankAccount::displayInfo();
    cout << "Overdraft Limit: $" << overdraft_limit << endl;
}