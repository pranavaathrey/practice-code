#include <iostream>
#include <string>
#include <vector>
using namespace std;

class BankManager;  // Forward declaration

class BankAccount {
private:
    string name;
    double balance;
    static int accountCount;  // static member to track total accounts

    static constexpr double MIN_BALANCE = 1000.0;
    static constexpr double MAX_WITHDRAWAL = 5000.0;
    static constexpr double MIN_DEPOSIT = 500.0;

public:
    // Constructor
    BankAccount(const string& accName, double initialDeposit) {
        if (initialDeposit >= MIN_BALANCE) {
            name = accName;
            balance = initialDeposit;
            ++accountCount;
            cout << "Account with name \"" << accName << "\" created, with an initial deposit of Rs. " 
                 << initialDeposit << "." << endl;
        } else {
            cerr << "Initial deposit must be at least Rs. " << MIN_BALANCE << ". Account not created.\n";
            name = "";
            balance = 0;
        }
    }

    // Deposit function
    void deposit(double amount) {
        if (amount >= MIN_DEPOSIT) {
            balance += amount;
            cout << "Deposited Rs. " << amount << " into account of " << name << ".\n";
        } else {
            cerr << "Deposit must be at least Rs. " << MIN_DEPOSIT << ". Transaction cancelled.\n";
        }
    }

    // Withdraw function
    void withdraw(double amount) {
        if (amount <= 0) {
            cerr << "Withdrawal amount must be positive. Transaction cancelled.\n";
            return;
        }
        if (amount > MAX_WITHDRAWAL) {
            cerr << "Cannot withdraw more than Rs. " << MAX_WITHDRAWAL << " in one transaction.\n";
            return;
        }
        if (balance - amount < MIN_BALANCE) {
            cerr << "Insufficient balance after withdrawal. Minimum balance of Rs. " << MIN_BALANCE << " must be maintained.\n";
            return;
        }
        balance -= amount;
        cout << "Withdrew Rs. " << amount << " from account of " << name << ".\n";
    }

    // Friend class declaration
    friend class BankManager;
};

// Definition of static member
int BankAccount::accountCount = 0;

// BankManager class
class BankManager {
public:
    static void displayTotalAccounts() {
        cout << "Total accounts created: " << BankAccount::accountCount << "\n";
    }

    static void displayAccountDetails(const BankAccount& acc) {
        if (acc.name.empty()) {
            cout << "Invalid account.\n";
            return;
        }
        cout << "Account Holder: " << acc.name << "\n";
        cout << "Balance: Rs. " << acc.balance << "\n";
    }
};

// Main function
int main() {
    vector<BankAccount> accounts;

    // Creating some accounts
    accounts.emplace_back("Alice", 5000);   // Valid
    accounts.emplace_back("Bob", 950);      // Invalid, won't be counted
    accounts.emplace_back("Charlie", 1200); // Valid

    cout << "\n--- Performing Transactions ---\n";

    // Valid deposit
    accounts[0].deposit(1000);   // Rs. 1000 deposited into Alice's account

    // Invalid deposit
    accounts[0].deposit(300);    // Below minimum

    // Valid withdrawal
    accounts[0].withdraw(4000);  // Within limit and leaves more than Rs. 1000

    // Invalid withdrawal (over Rs. 5000)
    accounts[1].withdraw(6000);  // Will not proceed

    // Invalid withdrawal (brings balance below Rs. 1000)
    accounts[2].withdraw(300);   // Only if balance would fall under min

    cout << "\n--- Account Details ---\n";
    for (const auto& acc : accounts) {
        BankManager::displayAccountDetails(acc);
        cout << "----------------------\n";
    }

    cout << "\n--- System Summary ---\n";
    BankManager::displayTotalAccounts();

    return 0;
}
