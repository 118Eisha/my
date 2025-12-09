#include "account.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <iomanip>
#include <ctime>
#include <cstdlib>

using namespace std;

// ======================== ACCOUNT CLASS IMPLEMENTATION ========================

// Default Constructor
Account::Account() : name(""), accountNumber(0), balance(0.0), accountType("General") {}

// Parameterized Constructor
Account::Account(string n, int accNum, double bal, string type) 
    : name(n), accountNumber(accNum), balance(bal), accountType(type) {}

// Destructor
Account::~Account() {}

// Deposit money into account
void Account::deposit(double amount) {
    if (amount <= 0) {
        throw InvalidAmountException("Deposit amount must be positive!");
    }
    
    balance += amount;
    cout << "\n✓ Successfully deposited $" << fixed << setprecision(2) << amount << endl;
    cout << "New balance: $" << balance << endl;
    
    // Update balance in file
    updateBalanceInFile();
}

// Withdraw money from account
void Account::withdraw(double amount) {
    if (amount <= 0) {
        throw InvalidAmountException("Withdrawal amount must be positive!");
    }
    
    if (amount > balance) {
        throw InsufficientFundsException(amount, balance);
    }
    
    balance -= amount;
    cout << "\n✓ Successfully withdrew $" << fixed << setprecision(2) << amount << endl;
    cout << "Remaining balance: $" << balance << endl;
    
    // Update balance in file
    updateBalanceInFile();
}

// Display current balance
void Account::displayBalance() const {
    cout << "\n========== BALANCE INFO ==========" << endl;
    cout << "Account Number: " << accountNumber << endl;
    cout << "Account Holder: " << name << endl;
    cout << "Current Balance: $" << fixed << setprecision(2) << balance << endl;
    cout << "==================================" << endl;
}

// Display full account information
void Account::displayAccountInfo() const {
    cout << "\n========== ACCOUNT DETAILS ==========" << endl;
    cout << "Account Number: " << accountNumber << endl;
    cout << "Account Holder: " << name << endl;
    cout << "Account Type: " << accountType << endl;
    cout << "Balance: $" << fixed << setprecision(2) << balance << endl;
    cout << "=====================================" << endl;
}

// Getters
string Account::getName() const { return name; }
int Account::getAccountNumber() const { return accountNumber; }
double Account::getBalance() const { return balance; }
string Account::getAccountType() const { return accountType; }

// Setters
void Account::setBalance(double bal) { balance = bal; }

// ======================== FILE HANDLING ========================

// Save new account to file
void Account::saveToFile() const {
    ofstream outFile("accounts.txt", ios::app);
    
    if (!outFile) {
        cerr << "Error: Could not open file for saving account!" << endl;
        return;
    }
    
    // Format: accountNumber|name|balance|accountType
    outFile << accountNumber << "|" 
            << name << "|" 
            << fixed << setprecision(2) << balance << "|" 
            << accountType << endl;
    
    outFile.close();
    cout << "\n✓ Account saved to file successfully!" << endl;
}

// Update balance in file after transaction
void Account::updateBalanceInFile() {
    ifstream inFile("accounts.txt");
    ofstream tempFile("temp.txt");
    
    if (!inFile || !tempFile) {
        cerr << "Error: Could not open files for updating!" << endl;
        return;
    }
    
    string line;
    bool found = false;
    
    while (getline(inFile, line)) {
        stringstream ss(line);
        string accNumStr, accName, balStr, accType;
        
        getline(ss, accNumStr, '|');
        getline(ss, accName, '|');
        getline(ss, balStr, '|');
        getline(ss, accType, '|');
        
        int fileAccNum = stoi(accNumStr);
        
        if (fileAccNum == accountNumber) {
            // Write updated record
            tempFile << accountNumber << "|" 
                    << name << "|" 
                    << fixed << setprecision(2) << balance << "|" 
                    << accountType << endl;
            found = true;
        } else {
            // Write original record
            tempFile << line << endl;
        }
    }
    
    inFile.close();
    tempFile.close();
    
    // Replace original file with updated file
    remove("accounts.txt");
    rename("temp.txt", "accounts.txt");
    
    if (found) {
        cout << "✓ Account balance updated in file!" << endl;
    }
}

// Load account from file by account number
Account* Account::loadAccountFromFile(int accNum) {
    ifstream inFile("accounts.txt");
    
    if (!inFile) {
        cerr << "Error: Could not open accounts file!" << endl;
        return nullptr;
    }
    
    string line;
    while (getline(inFile, line)) {
        stringstream ss(line);
        string accNumStr, accName, balStr, accType;
        
        getline(ss, accNumStr, '|');
        getline(ss, accName, '|');
        getline(ss, balStr, '|');
        getline(ss, accType, '|');
        
        int fileAccNum = stoi(accNumStr);
        
        if (fileAccNum == accNum) {
            double bal = stod(balStr);
            inFile.close();
            return new Account(accName, fileAccNum, bal, accType);
        }
    }
    
    inFile.close();
    return nullptr;
}

// Generate unique account number
int Account::generateUniqueAccountNumber() {
    // Seed random number generator
    static bool seeded = false;
    if (!seeded) {
        srand(time(0));
        seeded = true;
    }
    
    ifstream inFile("accounts.txt");
    int maxAccNum = 1000; // Starting account number
    
    if (inFile) {
        string line;
        while (getline(inFile, line)) {
            stringstream ss(line);
            string accNumStr;
            getline(ss, accNumStr, '|');
            
            int accNum = stoi(accNumStr);
            if (accNum > maxAccNum) {
                maxAccNum = accNum;
            }
        }
        inFile.close();
    }
    
    // Return next account number (auto-increment)
    return maxAccNum + 1;
}

// ======================== EXCEPTION CLASSES ========================

// InsufficientFundsException
InsufficientFundsException::InsufficientFundsException(double requested, double available) {
    stringstream ss;
    ss << "Insufficient funds! Requested: $" << fixed << setprecision(2) 
       << requested << ", Available: $" << available;
    message = ss.str();
}

InsufficientFundsException::~InsufficientFundsException() throw() {}

const char* InsufficientFundsException::what() const throw() {
    return message.c_str();
}

// InvalidAmountException
InvalidAmountException::InvalidAmountException(const string& msg) : message(msg) {}

InvalidAmountException::~InvalidAmountException() throw() {}

const char* InvalidAmountException::what() const throw() {
    return message.c_str();
}