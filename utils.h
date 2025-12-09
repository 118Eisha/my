#pragma once
#include <string>
using namespace std;

// Hash a password (simple demo, not secure!)
string simple_hash(const string& password);

// Validate account number (e.g. at least 5 digits, all numbers)
bool isValidAccountNumber(const string& account_number);

// Validate if a string is a valid double value
bool isValidDouble(const string& value);

// Convert string to lowercase
string toLower(const string& input);