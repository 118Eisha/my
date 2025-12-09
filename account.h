#ifndef ACCOUNT_H
#define ACCOUNT_H

#include <string>
#include <fstream>

class Account {
protected:
    std::string name;
    int accountNumber;
    double balance;
    std::string accountType;

public:
    // Constructors
    Account();
    Account(std::string n, int accNum, double bal, std::string type);
    
    // Virtual destructor for proper cleanup in derived classes
    virtual ~Account();
    
    // Core banking operations (virtual for polymorphism)
    virtual void deposit(double amount);
    virtual void withdraw(double amount);
    virtual void displayBalance() const;
    
    // Getters
    std::string getName() const;
    int getAccountNumber() const;
    double getBalance() const;
    std::string getAccountType() const;
    
    // Setters
    void setBalance(double bal);
    
    // File handling methods
    void saveToFile() const;
    void updateBalanceInFile();
    static Account* loadAccountFromFile(int accNum);
    
    // Helper function - generates unique account number
    static int generateUniqueAccountNumber();
    
    // Display account info (can be overridden)
    virtual void displayAccountInfo() const;
};

// Custom Exception Class
class InsufficientFundsException : public std::exception {
private:
    std::string message;
    
public:
    InsufficientFundsException(double requested, double available);
    virtual const char* what() const throw();
    virtual ~InsufficientFundsException() throw();
};

class InvalidAmountException : public std::exception {
private:
    std::string message;
    
public:
    InvalidAmountException(const std::string& msg);
    virtual const char* what() const throw();
    virtual ~InvalidAmountException() throw();
};

#endif