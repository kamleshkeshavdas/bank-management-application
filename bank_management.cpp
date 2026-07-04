#include <iostream>
#include <fstream>
#include <string>
using namespace std;

class Bank
{
    int accNo;
    string name;
    float balance;

public:
    void createAccount();
    void showAccount();
    int getAccNo();
    float getBalance();
    void deposit(float amt);
    void withdraw(float amt);
};

void Bank::createAccount()
{
    cout << "Enter account number : ";
    cin >> accNo;
    cin.ignore();

    cout << "Enter customer name : ";
    getline(cin, name);

    cout << "Enter initial balance : ";
    cin >> balance;
}

void Bank::showAccount()
{
    cout << "\nAccount Number : " << accNo << endl;
    cout << "Customer Name  : " << name << endl;
    cout << "Balance        : " << balance << endl;
}

int Bank::getAccNo()
{
    return accNo;
}

float Bank::getBalance()
{
    return balance;
}

void Bank::deposit(float amt)
{
    balance = balance + amt;
}

void Bank::withdraw(float amt)
{
    balance = balance - amt;
}

// create new account
void newAccount()
{
    Bank b;
    ofstream fout("bank.txt", ios::app);

    b.createAccount();
    fout.write((char*)&b, sizeof(b));

    fout.close();
    cout << "\nAccount created successfully...\n";
}

// display all accounts
void displayAll()
{
    Bank b;
    ifstream fin("bank.txt");

    cout << "\n===== ALL ACCOUNT DETAILS =====\n";

    while (fin.read((char*)&b, sizeof(b)))
    {
        b.showAccount();
        cout << "--------------------------\n";
    }

    fin.close();
}

// search account
void searchAccount()
{
    int no, found = 0;
    Bank b;
    ifstream fin("bank.txt");

    cout << "Enter account number to search : ";
    cin >> no;

    while (fin.read((char*)&b, sizeof(b)))
    {
        if (b.getAccNo() == no)
        {
            cout << "\nAccount found:\n";
            b.showAccount();
            found = 1;
            break;
        }
    }

    fin.close();

    if (found == 0)
        cout << "Account not found...\n";
}

// deposit money
void depositMoney()
{
    int no, found = 0;
    float amt;
    Bank b;
    fstream file;

    cout << "Enter account number : ";
    cin >> no;
    cout << "Enter amount to deposit : ";
    cin >> amt;

    file.open("bank.txt", ios::in | ios::out);

    while (file.read((char*)&b, sizeof(b)))
    {
        if (b.getAccNo() == no)
        {
            b.deposit(amt);

            int pos = file.tellg();
            file.seekp(pos - sizeof(b));
            file.write((char*)&b, sizeof(b));

            cout << "Amount deposited successfully...\n";
            found = 1;
            break;
        }
    }

    file.close();

    if (found == 0)
        cout << "Account not found...\n";
}

// withdraw money
void withdrawMoney()
{
    int no, found = 0;
    float amt;
    Bank b;
    fstream file;

    cout << "Enter account number : ";
    cin >> no;
    cout << "Enter amount to withdraw : ";
    cin >> amt;

    file.open("bank.txt", ios::in | ios::out);

    while (file.read((char*)&b, sizeof(b)))
    {
        if (b.getAccNo() == no)
        {
            if (amt > b.getBalance())
            {
                cout << "Insufficient balance...\n";
            }
            else
            {
                b.withdraw(amt);

                int pos = file.tellg();
                file.seekp(pos - sizeof(b));
                file.write((char*)&b, sizeof(b));

                cout << "Amount withdrawn successfully...\n";
            }

            found = 1;
            break;
        }
    }

    file.close();

    if (found == 0)
        cout << "Account not found...\n";
}

// check balance
void checkBalance()
{
    int no, found = 0;
    Bank b;
    ifstream fin("bank.txt");

    cout << "Enter account number : ";
    cin >> no;

    while (fin.read((char*)&b, sizeof(b)))
    {
        if (b.getAccNo() == no)
        {
            cout << "Current balance is : " << b.getBalance() << endl;
            found = 1;
            break;
        }
    }

    fin.close();

    if (found == 0)
        cout << "Account not found...\n";
}

int main()
{
    int ch;

    do
    {
        cout << "\n========== BANK MANAGEMENT SYSTEM ==========\n";
        cout << "1. Create New Account\n";
        cout << "2. Display All Accounts\n";
        cout << "3. Search Account\n";
        cout << "4. Deposit Money\n";
        cout << "5. Withdraw Money\n";
        cout << "6. Check Balance\n";
        cout << "7. Exit\n";
        cout << "Enter your choice : ";
        cin >> ch;

        switch (ch)
        {
        case 1:
            newAccount();
            break;

        case 2:
            displayAll();
            break;

        case 3:
            searchAccount();
            break;

        case 4:
            depositMoney();
            break;

        case 5:
            withdrawMoney();
            break;

        case 6:
            checkBalance();
            break;

        case 7:
            cout << "Exiting...\n";
            break;

        default:
            cout << "Wrong choice...\n";
        }

    } while (ch != 7);

    return 0;
}