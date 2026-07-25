#include<bits/stdc++.h>
using namespace std;

class Non_Withdrawable_Account{
    public:
    virtual void deposit(double amount) = 0;
};

class Withdrawable_Account:public Non_Withdrawable_Account{
   public:
   virtual void withdraw(double amount)=0;
};

class Current_Account: public Withdrawable_Account{
    double balance;
   public:
   Current_Account(double initialBalance=0){
        this->balance = initialBalance;
   }

    void deposit(double amount) override{
      balance += amount;
   }

   void withdraw(double amount) override{
      if(balance<amount){
        throw "Low Account Balance!!";
      }
      balance -= amount;
   }
};


class Savings_Account:public Withdrawable_Account{
   double balance;
   public:
   Savings_Account(double initialBalance=0){
        this->balance = initialBalance;
   }
   void deposit(double amount) override{
      balance += amount;
   }

   void withdraw(double amount) override{
      if(balance<amount){
        throw "Low Account Balance!!";
      }
      balance -= amount;
   }
};

class Fixed_Deposit_Account:public Non_Withdrawable_Account{
    double balance;
    public:
    Fixed_Deposit_Account(double initialBalance = 0){
         this->balance = initialBalance;
    }
   void deposit(double amount) override{
      balance += amount;
   }
};

int main(){

}