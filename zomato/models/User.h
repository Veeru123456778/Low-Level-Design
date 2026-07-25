#include<bits/stdc++.h>
#include "Cart.h"
using namespace std;

class User{
    private:
    string userName;
    string address;
    string phoneNum;
    Cart* cart;

    public:

    User(string& userN,string& add,string& pNum){
      userName = userN;
      address = add;
      phoneNum = pNum;
      cart = new Cart();
    }

    ~User(){
       delete cart;
    }
};
int main(){

}