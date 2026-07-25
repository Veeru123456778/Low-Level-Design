#include<bits/stdc++.h>
using namespace std;

class MenuItem{
   private:
   string itemCode;
   string itemName;
   double itemPrice;

   public:
   
   MenuItem(string& code,string& name,double price){
     itemCode = code;
     itemName = name;
     itemPrice = price;
   }
   ~MenuItem(){
      cout<<"Destroying item with code "<<itemCode<<" and name :"<<itemName<<endl;
   }
   string getItemCode(){
      return itemCode;
   }
   string getItemName(){
      return itemName;
   }
   double getItemPrice(){
    return itemPrice;
   }
};

int main(){
    
}