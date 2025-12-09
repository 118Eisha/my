#pragma once
#include "bankaccount.h"
using namespace std;

class CheckingAccount : public BankAccount {
public:
    CheckingAccount();
    CheckingAccount(const string& account_number, const string& owner_name, const string& password_hash, double balance, double overdraft_limit);
    virtual ~CheckingAccount();

    bool withdraw(double amount) override;
    string toCSV() const override;
    void fromCSV(const string& line) override;
    void displayInfo() const override;

private:
    double overdraft_limit;
};