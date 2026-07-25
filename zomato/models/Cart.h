#include<bits/stdc++.h>
#include "MenuItem.h"
#include "Restaurant.h"
using namespace std;

class Cart{
    private:
      Restaurant* restaurant;
      vector<MenuItem*> itemsInCart;
      
    public:
      Cart(){
        restaurant = nullptr;
      }
      
      void addToCart(MenuItem* item){
        if(restaurant==nullptr){
            cout<<"Firstly choose the restaurant!!"<<endl;
            return;
        }
        itemsInCart.push_back(item);
      }
      vector<MenuItem*> getItems(){
          return itemsInCart;
      }

      double getTotalCost(){
        double sum = 0;
        for(auto&item:itemsInCart){
            sum += item->getItemPrice();
        }
        return sum;
      }

      bool isEmpty(){
        return (!restaurant || itemsInCart.empty());
      }
      
      void clear(){
        restaurant = NULL;
        itemsInCart.clear();
      }
};

int main(){

}