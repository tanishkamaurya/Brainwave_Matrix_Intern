#include<bits/stdc++.h>
using namespace std;

class Account{
    private:
    int accountNum;
    string ownerName;
    double balance;

    public:
    //constructor initialisation
    //constructor(special function, no return type(not even void)) automatically called when object is created
    Account(int accNum, string name, double initialBalance){ //CONSTRUCTOR
        accountNum = accNum; //Assigns the parameter accNum to the object's(Account) accountNumber attribute
        ownerName = name;
        balance = initialBalance;
    } //IF OBJECT IS CREATED, CONSTRUCTOR HELPS ASSIGN VARIOUS VALUES
    
    int getAccountNumber() const { return accountNum;} //fn returns int type, const -- does not let modify class attributes
    string getownerName() const {return ownerName; }
    double getBalance() const { return balance; }

    void deposit(double amount){
        if(amount>0){
            balance+=amount;
            cout<<"Deposited Rs."<<amount<<"successfully. \n";
        }
        else{
            cout<<"Invalid deposit amount. \n";
        }
    }

    bool withdraw(double amount){
        if(amount>0 && amount<=balance){
            balance-=amount;
            cout<<"Withdrawn Rs."<<amount<<"successfully. \n";
            return true;
        }
        else{
            cout<<"Insuffiecient funds. \n";
            return false;  
        }
    }

    bool transfer(Account &receiver, double amount){
        if(withdraw(amount)){
            receiver.deposit(amount);
            cout<<"Transferred Rs. "<<amount<< "to"<<receiver.getownerName()<<".\n";
            return true;
        }
        return false;
    }

    void display() const{
        cout<<"Account Number : "<<accountNum<<"\n";
        cout<<"Owner name : "<<ownerName<<"\n";
        cout<<"Balance : Rs."<<balance<< "\n";
    }

    void saveTofile(ofstream &file) const{
        file <<accountNum<< " " <<ownerName<< " " <<balance<< "\n";
    }
};

class Bank{
    private:
    vector<Account> accounts;
    int nextAccountnum = 1000;

public:
Bank(){ loadAccountsFromFile(); }
~Bank() { saveAccountsToFile(); }

void createAccount(){
    string name;
    double initialBalance;
    cout<<"Enter account holder's name: ";
    cin.ignore();
    getline(cin, name);
    cout<<"Enter initial balance: ";
    cin>>initialBalance;

    if(initialBalance < 0){
        cout<<"Initial balance cannot be negative. \n";
        return;
    }

    accounts.push_back(Account(nextAccountnum++, name, initialBalance));
    cout<<"Account created successfully! Your account number is "<<accounts.back().getAccountNumber()<<". \n";
}

Account* findAccount(int accNumber){
    for(auto &acc : accounts){
        if(acc.getAccountNumber() == accNumber){
            return &acc;
        }
    }
    cout<<"Account not found. \n";
    return nullptr;
}

void depositFunds(){
    int accNumber;
    double amount;
    cout<<"Enter account number:";
    cin>>accNumber;
    Account* acc = findAccount(accNumber);
    if(acc){
        cout<<"Enter deposit amount";
        cin>>amount;
        acc->deposit(amount);
    }
}

void withdrawFunds(){
    int accNumber;
    double amount;
    cout<<"Enter account number: ";
    cin>>accNumber;
    Account* acc = findAccount(accNumber);
    if(acc){
        cout<<"Enter withdrawl amount :";
        cin>>amount;
        acc->withdraw(amount);
    }
}

void transferFunds(){
    int senderAcc, receiverAcc;
    double amount;
    cout<<"Enter sender account number";
    cin>>senderAcc;
    cout<<"Enter receiver account number";
    cin>>receiverAcc;
    cout<<"Enter amount to transfer :";
    cin>>amount;

    Account* sender = findAccount(senderAcc);
    Account* receiver = findAccount(receiverAcc);   
    if(sender && receiver){
        sender->transfer(*receiver, amount);
    }
}

void viewAccount(){
    int accNumber;
    cout<<"Enter account number : ";
    cin>>accNumber;
    Account* acc = findAccount(accNumber);
    if(acc){
        acc->display();
    }
}

void saveAccountsToFile() const{
    ofstream file("accounts.txt"); //opens or creates a file called "accounts.txt"
    //ofstream - output file operations
    if(!file){ //file doesnot open
        cout<<"Error saving account. \n";
        return;
    }
    //iterator acc loops throught vector accounts
    for(const auto &acc: accounts){
        acc.saveTofile(file);
    }
    file.close(); //file closing to avoid data corruption
}

void loadAccountsFromFile(){
    ifstream file("accounts.txt");
    if(!file) return;

    int accNum;
    string name;
    double balance;
    while(file >> accNum){
        file.ignore();
        getline(file, name);
        file>>balance;
        accounts.push_back(Account(accNum, name, balance));
        if(accNum >= nextAccountnum){
            nextAccountnum = accNum + 1;
        }
    }
    file.close();
}
};

    
int main(){
    Bank bank;
    int choice;
    do {
        cout << "\n--- Online Banking System ---\n";
        cout << "1. Create Account\n";
        cout << "2. Deposit Funds\n";
        cout << "3. Withdraw Funds\n";
        cout << "4. Transfer Funds\n";
        cout << "5. View Account\n";
        cout << "6. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch(choice){
            case 1:
                bank.createAccount();
                break;
            case 2:
                bank.depositFunds();
                break;
            case 3:
                bank.withdrawFunds();
                break;
            case 4:
                bank.transferFunds();
                break; 
            case 5:
                bank.viewAccount();
                break;
            case 6:
                cout<<"Exiting program.. \n";
                break;   
            default:
                cout<<"Invalid choice.Try again \n";
        }
    }while(choice!=6);
    //atm.start();
    return 0;

}