#include<bits/stdc++.h>
#include "Restaurant.h"
#include "MenuItem.h"
#include "User.h"
using namespace std;

class Order{
    private:
    Restaurant* restaurant;
    static int nextOrderId;
    vector<MenuItem*> items;
    int orderId;
    User* user;
    // PaymentStrategy* p;
    double totalAmount;
    string scheduled;

    public:
    
    Order(){
      user = nullptr;
      restaurant = nullptr;
      totalAmount = 0.0;
      scheduled = "";
      orderId = nextOrderId;
      nextOrderId++;
    }

    ~Order(){

    }
    
};

int Order::nextOrderId = 1;
int main(){

}