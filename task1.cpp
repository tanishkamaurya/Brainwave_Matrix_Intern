#include<bits/stdc++.h>
using namespace std;

class ATM{
    private:
    unordered_map<int, pair<int, int>> accounts; //accountNum -> pin, balance
    int currentAcc;

    bool authenticate(int accountNum, int pin){
        if(accounts.find(accountNum)!=accounts.end() && (accounts[accountNum].first==pin)){
            currentAcc = accountNum;
            return true;
        }
        return false;
    }

    public:
    void createAccount(){
        int pin, balance;
        int accountNum;
        cout<<"Enter accountNum \n";
        cin>>accountNum;

        if(accounts.find(accountNum)!=accounts.end()){
            cout<<"Account already exists, please try again";
            return; 
        }
        
        cout<<"Enter 4-digit pin \n";
        cin>>pin;

        cout<<"Enter intital deposit amount \n";
        cin>>balance;

        accounts[accountNum]={pin, balance};
        cout<<"Account created successfully";
    }
    void start(){
        int accountNum;
        int pin;

        cout<<"Enter account number :";
        cin>>accountNum;
        cout<<"Enter PIN :";
        cin>>pin;

        if(!authenticate(accountNum, pin)){
            cout<<"Invalid credentials \n Exiting..";
        }

        int choice;
        do{
            cout<<"1.Check balance \n 2.Deposit \n 3.Withdraw \n 4.Exit";
            cin>>choice;

            switch(choice){
            case 1:
            cout<<"Current Balance : Rs."<<accounts[accountNum].second;
            break;

            case 2:
            int deposit;
            cout<<"Enter deposit ammount";
            cin>>deposit;
            accounts[accountNum].second += deposit;
            cout<<"Amount deposited succesfully \n Updated balance: Rs"<<accounts[accountNum].second;
            

            case 3:
            int amount;
            cout<<"Enter withdrawl amount";
            cin>>amount;
            int balance = accounts[accountNum].second;
            if(amount>balance){
            cout<<"Insufficient funds \n";
            }
            else{
                accounts[accountNum].second -= amount;
                cout<<"Withdrawl successful \n Updated balance : Rs"<<accounts[accountNum].second;
            }
            break;

            case 4:
            cout<<"Thank you for using our ATM \n Exiting..";
            break;
            

            default:
                cout<<"Invalid choice, try again";
            }
        } while(choice!=4);
    }

};

int main(){
    ATM atm;
    int option;
    do{
        cout<<"\n 1. Creat Account \n 2. Use ATM \n 3.Exit \n Choose an option: ";
        cin>>option;

        switch(option){
            case 1:
                atm.createAccount();
                break;
            case 2:
                atm.start();
                break;
            case 3:
                cout<<"Exiting ATM system. Goodbye! \n";
                break;
            default:
                cout<<"Invalid option.Try again \n";
        }
    }while(option!=3);
    //atm.start();
    return 0;

}