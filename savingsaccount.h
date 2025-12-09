#pragma once
#include "bankaccount.h"
using namespace std;

class SavingsAccount : public BankAccount {
public:
    SavingsAccount();
    SavingsAccount(const string& account_number, const string& owner_name, const string& password_hash, double balance);
    virtual ~SavingsAccount();

    void applyInterest(double rate);
    string toCSV() const override;
    void fromCSV(const string& line) override;
    void displayInfo() const override;
};