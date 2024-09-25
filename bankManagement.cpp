#include <iostream>
#include <map>
#include <vector>
#include <string>
#include <iomanip>  
using namespace std;

// Class for Authentication (Basic Security)
class Security {
private:
    string adminUsername = "admin";
    string adminPassword = "admin123";
    
public:
    // Authentication function for admin login
    bool login(string username, string password) {
        if (username == adminUsername && password == adminPassword) {
            cout << "Login successful!" << endl;
            return true;
        } else {
            cout << "Invalid credentials! Access denied." << endl;
            return false;
        }
    }
};

// Account Class to manage individual customer accounts
class Account {
private:
    int accountNumber;
    string accountHolderName;
    double balance;

public:
    // Default constructor
    Account() : accountNumber(0), accountHolderName("Unnamed Account"), balance(0.0) {}

    // Parameterized constructor
    Account(int accNum, string accName, double initialBalance)
        : accountNumber(accNum), accountHolderName(accName), balance(initialBalance) {}

    // Function to deposit money into the account
    void deposit(double amount) {
        if (amount > 0) {
            balance += amount;
            cout << "Deposited $" << amount << " to account #" << accountNumber << endl;
        } else {
            cout << "Invalid deposit amount!" << endl;
        }
    }

    // Function to withdraw money from the account
    bool withdraw(double amount) {
        if (amount > balance) {
            cout << "Insufficient funds!" << endl;
            return false;
        } else if (amount <= 0) {
            cout << "Invalid withdrawal amount!" << endl;
            return false;
        } else {
            balance -= amount;
            cout << "Withdrew $" << amount << " from account #" << accountNumber << endl;
            return true;
        }
    }

    // Function to transfer money between accounts
    bool transfer(Account& toAccount, double amount) {
        if (withdraw(amount)) {
            toAccount.deposit(amount);
            cout << "Transferred $" << amount << " from account #" << accountNumber << " to account #" << toAccount.accountNumber << endl;
            return true;
        }
        return false;
    }

    // Function to display account details
    void displayAccount() const {
        cout << fixed << setprecision(2);  // Display the balance with 2 decimal places
        cout << "Account Number: " << accountNumber << endl;
        cout << "Account Holder: " << accountHolderName << endl;
        cout << "Balance: $" << balance << endl;
    }

    // Function to generate account statement (display transactions)
    void generateStatement() const {
        cout << "Account Statement for #" << accountNumber << ":\n";
        displayAccount();  // Currently, it shows basic details
        // In a real-world application, this would display the transaction history
    }

    // Getters
    int getAccountNumber() const { return accountNumber; }
    string getAccountHolderName() const { return accountHolderName; }
    double getBalance() const { return balance; }

    // Setters
    void setAccountHolderName(const string& name) { accountHolderName = name; }
};



// Bank Class to manage multiple accounts
class Bank {
private:
    map<int, Account> accounts;
    int nextAccountNumber = 1001;

public:
    // Create a new account
    void createAccount(string accountHolderName, double initialDeposit) {
        Account newAccount(nextAccountNumber, accountHolderName, initialDeposit);
        accounts[nextAccountNumber] = newAccount;
        cout << "Account created successfully. Account Number: " << nextAccountNumber << endl;
        nextAccountNumber++;
    }

    // Deposit money into an account
    void deposit(int accountNumber, double amount) {
        auto it = accounts.find(accountNumber);
        if (it != accounts.end()) {
            it->second.deposit(amount);
        } else {
            cout << "Account not found!" << endl;
        }
    }

    // Withdraw money from an account
    void withdraw(int accountNumber, double amount) {
        auto it = accounts.find(accountNumber);
        if (it != accounts.end()) {
            it->second.withdraw(amount);
        } else {
            cout << "Account not found!" << endl;
        }
    }

    // Transfer funds between two accounts
    void transfer(int fromAccount, int toAccount, double amount) {
        auto fromIt = accounts.find(fromAccount);
        auto toIt = accounts.find(toAccount);

        if (fromIt != accounts.end() && toIt != accounts.end()) {
            if (fromIt->second.withdraw(amount)) {
                toIt->second.deposit(amount);
                cout << "Transfer successful!" << endl;
            } else {
                cout << "Transfer failed due to insufficient balance." << endl;
            }
        } else {
            cout << "One or both accounts not found!" << endl;
        }
    }

    // Display account details
    void displayAccountDetails(int accountNumber) const {
        auto it = accounts.find(accountNumber);
        if (it != accounts.end()) {
            it->second.displayAccount();
        } else {
            cout << "Account not found!" << endl;
        }
    }

    // Display account transaction history
    void displayTransactionHistory(int accountNumber) const {
        auto it = accounts.find(accountNumber);
        if (it != accounts.end()) {
            it->second.generateStatement();
        } else {
            cout << "Account not found!" << endl;
        }
    }

    // Delete an account
    void deleteAccount(int accountNumber) {
        auto it = accounts.find(accountNumber);
        if (it != accounts.end()) {
            accounts.erase(it);
            cout << "Account deleted successfully." << endl;
        } else {
            cout << "Account not found!" << endl;
        }
    }
};

// Main function to run the system
int main() {
    Bank bank;
    Security security;
    int choice, accountNumber;
    string username, password, name;
    double amount;

    // Login for security
    cout << "Welcome to the Bank Management System" << endl;
    cout << "Please login to access the system." << endl;
    cout << "Username: ";
    cin >> username;
    cout << "Password: ";
    cin >> password;

    if (!security.login(username, password)) {
        return 0; // Exit if login fails
    }

    // Main loop to interact with the bank system
    while (true) {
        cout << "\n--- Bank Management System ---" << endl;
        cout << "1. Create Account" << endl;
        cout << "2. Deposit" << endl;
        cout << "3. Withdraw" << endl;
        cout << "4. Transfer" << endl;
        cout << "5. Display Account Details" << endl;
        cout << "6. Display Transaction History" << endl;
        cout << "7. Delete Account" << endl;
        cout << "8. Exit" << endl;
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
        case 1:
            cout << "Enter Account Holder Name: ";
            cin.ignore();  // To ignore any leftover newline character
            getline(cin, name);  // Using getline to allow multi-word names
            cout << "Enter Initial Deposit: ";
            cin >> amount;
            bank.createAccount(name, amount);
            break;

        case 2:
            cout << "Enter Account Number: ";
            cin >> accountNumber;
            cout << "Enter Amount to Deposit: ";
            cin >> amount;
            bank.deposit(accountNumber, amount);
            break;

        case 3:
            cout << "Enter Account Number: ";
            cin >> accountNumber;
            cout << "Enter Amount to Withdraw: ";
            cin >> amount;
            bank.withdraw(accountNumber, amount);
            break;

        case 4:
            int fromAccount, toAccount;
            cout << "Enter From Account Number: ";
            cin >> fromAccount;
            cout << "Enter To Account Number: ";
            cin >> toAccount;
            cout << "Enter Amount to Transfer: ";
            cin >> amount;
            bank.transfer(fromAccount, toAccount, amount);
            break;

        case 5:
            cout << "Enter Account Number: ";
            cin >> accountNumber;
            bank.displayAccountDetails(accountNumber);
            break;

        case 6:
            cout << "Enter Account Number: ";
            cin >> accountNumber;
            bank.displayTransactionHistory(accountNumber);
            break;

        case 7:
            cout << "Enter Account Number to Delete: ";
            cin >> accountNumber;
            bank.deleteAccount(accountNumber);
            break;

        case 8:
            cout << "Exiting..." << endl;
            return 0;

        default:
            cout << "Invalid choice! Please try again." << endl;
        }
    }

    return 0;
}
