#include <iostream>
#include <string>
using namespace std;

class Transaction {
public:
    virtual void processTransaction(double amount) = 0;
    virtual ~Transaction() {}
};

class Deposit : public Transaction {
public:
    void processTransaction(double amount) override {
        cout << "Deposit: " << amount << endl;
    }
};

class Withdrawal : public Transaction {
public:
    void processTransaction(double amount) override {
        cout << "Withdrawal: " << amount << endl;
    }
};

class BankAccount {
protected:
    string accountNumber;
    double balance;

public:
    BankAccount(const string &accNum) : accountNumber(accNum), balance(0.0) {}

    virtual void deposit(double amount) {
        balance += amount;
        Deposit deposit;
        deposit.processTransaction(amount);
    }

    virtual void withdraw(double amount) {
        if (balance >= amount) {
            balance -= amount;
            Withdrawal withdrawal;
            withdrawal.processTransaction(amount);
        } else {
            cout << "Insufficient funds!" << endl;
        }
    }

    double getBalance() const {
        return balance;
    }

    virtual ~BankAccount() {}
};

class SavingsAccount : public BankAccount {
public:
    SavingsAccount(const string &accNum) : BankAccount(accNum) {}

    void withdraw(double amount) override {
        if (balance >= amount) {
            BankAccount::withdraw(amount);
        } 
        else {
            cout << "Savings Account: Insufficient funds!" << endl;
        }
    }
};

class CheckingAccount : public BankAccount {
public:
    CheckingAccount(const string &accNum) : BankAccount(accNum) {}

    void withdraw(double amount) override {
        BankAccount::withdraw(amount);
    }
};

class Customer {
private:
    string name;
    BankAccount *account;

public:
    Customer(const string &name, BankAccount *acc) : name(name), account(acc) {}

    void deposit(double amount) {
        account->deposit(amount);
    }

    void withdraw(double amount) {
        account->withdraw(amount);
    }

    void showAccount() const {
        cout << "Customer: " << name << endl;
        cout << "Account Balance: " << account->getBalance() << endl;
    }

    ~Customer() {
        delete account;
    }
};

int main() {
    Customer customer1("Petr Ivanovich", new SavingsAccount("S123"));
    Customer customer2("Ivan Petrovich", new CheckingAccount("C456"));

    customer1.deposit(1000);
    customer2.deposit(500);
    
    customer1.withdraw(200);
    customer2.withdraw(600);

    customer1.showAccount();
    customer2.showAccount();
    
    return 0;
}