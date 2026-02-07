#include <iostream>
#include <string>
#include <vector>
using namespace std;

class BankManager; 

class BankAccount {
private:
    string name;
    double balance;
    static int accountCount;

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

    friend class BankManager;
};

int BankAccount::accountCount = 0;

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

int main() {
    vector<BankAccount> accounts;

    accounts.emplace_back("Alice", 5000);   
    accounts.emplace_back("Bob", 950);    
    accounts.emplace_back("Charlie", 1200); 

    cout << "\n--- Performing Transactions ---\n";

    accounts[0].deposit(1000); 

    accounts[0].deposit(300);   

    accounts[0].withdraw(4000); 

    accounts[1].withdraw(6000);  

    accounts[2].withdraw(300);   

    cout << "\n--- Account Details ---\n";
    for (const auto& acc : accounts) {
        BankManager::displayAccountDetails(acc);
        cout << "----------------------\n";
    }

    cout << "\n--- System Summary ---\n";
    BankManager::displayTotalAccounts();

    return 0;
}
