#include "transaction.h"
#include <sstream>
#include <iomanip>
#include <ctime>

Transaction::Transaction() : account_number(""), type(""), amount(0.0), balance_after(0.0), timestamp(""), description("") {}

Transaction::Transaction(const string& account_number,
                         const string& type,
                         double amount,
                         double balance_after,
                         const string& timestamp,
                         const string& description)
    : account_number(account_number),
      type(type),
      amount(amount),
      balance_after(balance_after),
      timestamp(timestamp),
      description(description) {}

string Transaction::toCSV() const {
    stringstream ss;
    ss << account_number << "," << type << "," << amount << "," << balance_after << "," << timestamp << "," << description;
    return ss.str();
}

Transaction Transaction::fromCSV(const string& line) {
    stringstream ss(line);
    string account, typ, amt_str, bal_str, time, desc;
    getline(ss, account, ',');
    getline(ss, typ, ',');
    getline(ss, amt_str, ',');
    getline(ss, bal_str, ',');
    getline(ss, time, ',');
    getline(ss, desc);
    double amt = stod(amt_str);
    double bal = stod(bal_str);
    return Transaction(account, typ, amt, bal, time, desc);
}

string Transaction::currentTimestamp() {
    time_t now = time(0);
    tm* ltm = localtime(&now);
    stringstream ss;
    ss << std::put_time(ltm, "%Y-%m-%d %H:%M:%S");
    return ss.str();
}