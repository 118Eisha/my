#pragma once
#include <string>
using namespace std;

class BankAccount {
public:
    BankAccount();
    BankAccount(const string& account_number, const string& owner_name, const string& password_hash, double balance);
    virtual ~BankAccount();

    virtual void deposit(double amount);
    virtual bool withdraw(double amount);
    virtual string toCSV() const;
    virtual void fromCSV(const string& line);

    virtual string getAccountNumber() const;
    virtual bool verifyPassword(const string& password) const;
    virtual double getBalance() const;
    virtual void setPasswordHash(const string& new_hash);
    virtual void displayInfo() const;

protected:
    string account_number;
    string owner_name;
    string password_hash;
    double balance;
};