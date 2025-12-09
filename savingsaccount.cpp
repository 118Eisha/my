#include "savingsaccount.h"
#include <iostream>
#include <sstream>

SavingsAccount::SavingsAccount() : BankAccount() {}

SavingsAccount::SavingsAccount(const string& account_number, const string& owner_name, const string& password_hash, double balance)
    : BankAccount(account_number, owner_name, password_hash, balance) {}

SavingsAccount::~SavingsAccount() {}

void SavingsAccount::applyInterest(double rate) {
    if (rate > 0) {
        double interest = balance * rate;
        balance += interest;
        std::cout << "Applied interest: $" << interest << ". New balance: $" << balance << std::endl;
    }
}

string SavingsAccount::toCSV() const {
    stringstream ss;
    ss << account_number << "," << owner_name << "," << password_hash << "," << balance;
    return ss.str();
}

void SavingsAccount::fromCSV(const string& line) {
    stringstream ss(line);
    string bal_str;
    getline(ss, account_number, ',');
    getline(ss, owner_name, ',');
    getline(ss, password_hash, ',');
    getline(ss, bal_str, ',');
    balance = stod(bal_str);
}

void SavingsAccount::displayInfo() const {
    cout << "Savings Account\n";
    BankAccount::displayInfo();
}