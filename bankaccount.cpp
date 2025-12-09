#include "bankaccount.h"
#include <iostream>
#include <sstream>

BankAccount::BankAccount() : account_number(""), owner_name(""), password_hash(""), balance(0.0) {}

BankAccount::BankAccount(const string& ac, const string& ow, const string& ph, double bal)
    : account_number(ac), owner_name(ow), password_hash(ph), balance(bal) {}

BankAccount::~BankAccount() {}

void BankAccount::deposit(double amount) {
    balance += amount;
}

bool BankAccount::withdraw(double amount) {
    if (balance >= amount) {
        balance -= amount;
        return true;
    }
    return false;
}

string BankAccount::toCSV() const {
    stringstream ss;
    ss << account_number << "," << owner_name << "," << password_hash << "," << balance;
    return ss.str();
}

void BankAccount::fromCSV(const string& line) {
    stringstream ss(line);
    string bal_str;
    getline(ss, account_number, ',');
    getline(ss, owner_name, ',');
    getline(ss, password_hash, ',');
    getline(ss, bal_str, ',');
    balance = stod(bal_str);
}

string BankAccount::getAccountNumber() const {
    return account_number;
}

bool BankAccount::verifyPassword(const string& password) const {
    return password_hash == password;
}

double BankAccount::getBalance() const {
    return balance;
}

void BankAccount::setPasswordHash(const string& new_hash) {
    password_hash = new_hash;
}

void BankAccount::displayInfo() const {
    cout << "Account Number: " << account_number << "\n"
         << "Owner Name: " << owner_name << "\n"
         << "Balance: $" << balance << endl;
}