#pragma once
#include <string>
using namespace std;

class Transaction {
public:
    Transaction();
    Transaction(const string& account_number,
                const string& type,
                double amount,
                double balance_after,
                const string& timestamp,
                const string& description);

    string toCSV() const;
    static Transaction fromCSV(const string& line);
    static string currentTimestamp();

    // Member variables
    string account_number;
    string type;
    double amount;
    double balance_after;
    string timestamp;
    string description;
};