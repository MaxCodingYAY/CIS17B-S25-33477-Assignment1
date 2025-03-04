#include <iostream>
#include <string>
#include <vector>

using namespace std;

class BankAccount {
private:
    string accountHolderName;
    int accountNumber;
    double balance;

public:
    // Constructor initilize bank account: name number etc
    BankAccount(string name, int accountNum, double initialBal) {
        accountHolderName = name;
        accountNumber = accountNum;
        balance = initialBal;
    }

    // deposit function adds input to balance
    void deposit(double amount) {
        if (amount <= 0) {
            cout << "Invalid: Deposit amount must be positive." << endl;
            return;
        }
        balance += amount;
        cout << "Deposit successful! New balance: $" << balance << endl;
    }

    // withdraw Function takes out amount from balance
    void withdraw(double amount) {
        if (amount <= 0) {
            cout << "Invalid: Withdrawal amount must be positive." << endl;
            return;
        }
        if (amount > balance) {
            cout << "Insufficient funds!" << endl;
            return;
        }
        balance -= amount;
        cout << "Withdrawal successful! New balance: $" << balance << endl;
    }

    // display balance 
    double getBalance() const {
        return balance;
    }

    // Display account info 
    void displayAccountInfo() const {
        cout << "Account Holder: " << accountHolderName << endl;
        cout << "Account Number: " << accountNumber << endl;
        cout << "Balance: $" << balance << endl;
    }
    // acccount number this is important to switch between accounts
    int getAccountNumber() const {
        return accountNumber;
    }
};

// create account numbers for each new account
int generateAccountNumber() {
    static int accountNumber = 100; // Starting account number
    return accountNumber++;
}

int main() {
    vector<BankAccount> accounts;
    BankAccount* currentAcc = nullptr;
    int choice;
    // menu basically the whole menu and lets you choose between them
    cout << "\nWelcome to Simple Bank System" << endl;
    while (true) {
        cout << "\n1. Create Account" << endl;
        cout << "2. Deposit Money" << endl;
        cout << "3. Withdraw Money" << endl;
        cout << "4. Check Balance" << endl;
        cout << "5. Switch Account" << endl;
        cout << "6. Exit" << endl;
        cout << "\nEnter your choice: ";

        if (!(cin >> choice)) {
            cin.clear();
            cin.ignore(1000, '\n');
            cout << "Invalid input. Please enter a number between 1-6." << endl;
            continue;
        }
        // start of switch
        switch (choice) {
        case 1: {
            //create accpimt case
            string name;
            double initialDep;
            cout << "Enter account holder name: ";
            cin.ignore();
            getline(cin, name);

            cout << "Enter initial deposit: ";
            if (!(cin >> initialDep) || initialDep < 0) {
                cin.clear();
                cin.ignore(1000, '\n');
                cout << "Invalid amount! Please enter a valid deposit amount." << endl;
                break;
            }
            // fix error
            int accountNum = generateAccountNumber();
            accounts.emplace_back(name, accountNum, initialDep);
            currentAcc = &accounts.back();

            cout << "Account created successfully! Your account number is " << accountNum << endl;
            break;
        }
        case 2: {
            //deposit the money  hhas to be pos
            if (!currentAcc) {
                cout << "No active account. Please create an account first." << endl;
                break;
            }
            double amount;
            cout << "Enter amount to deposit: ";
            if (!(cin >> amount)) {
                cin.clear();
                cin.ignore(1000, '\n');
                cout << "Invalid input! Please enter a valid number." << endl;
                break;
            }
            currentAcc->deposit(amount);
            break;
        }
        case 3: {
            //withdraw the money only if theres enough in account
            if (!currentAcc) {
                cout << "No active account. Please create an account first." << endl;
                break;
            }
            double amount;
            cout << "Enter amount to withdraw: ";
            if (!(cin >> amount)) {
                cin.clear();
                cin.ignore(1000, '\n');
                cout << "Invalid input! Please enter a valid number." << endl;
                break;
            }
            currentAcc->withdraw(amount);
            break;
        }
        case 4: {
            // displays bal
            if (!currentAcc) {
                cout << "No active account. Please create an account first." << endl;
                break;
            }
            cout << "Current balance: $" << currentAcc->getBalance() << endl;
            break;
        }
        case 5: {
            // switch accounts and inds it through bool
            if (accounts.empty()) {
                cout << "No accounts available. Please create an account first." << endl;
                break;
            }
            int accountNum;
            cout << "Enter account number to switch to: ";
            if (!(cin >> accountNum)) {
                cin.clear();
                cin.ignore(1000, '\n');
                cout << "Invalid input! Please enter a valid number." << endl;
                break;
            }
            // find account 
            bool found = false;
            for (auto& acc : accounts) {
                if (acc.getAccountNumber() == accountNum) {
                    currentAcc = &acc;
                    found = true;
                    cout << "Switched to account " << accountNum << endl;
                    break;
                }
            }
            if (!found) {
                cout << "Account not found!" << endl;
            }
            break;
        }
        case 6:
            //exits
            cout << "Thank you for using Simple Bank System!" << endl;
            return 0;
        default:
            cout << "Invalid choice! Please enter a number between 1-6." << endl;
        }
    }
    return 0;
}
