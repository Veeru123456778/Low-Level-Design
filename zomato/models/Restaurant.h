#ifndef RESTAURANT_H
#define RESTAURANT_H

#include<bits/stdc++.h>
#include "MenuItem.h"
using namespace std;
 
class Restaurant{
  private:
  int id;
  string name;
  string address;
  static int nextRestaurantId ;
  vector<MenuItem*> menu; 

  public:
  Restaurant(string n,string add){
     id = nextRestaurantId;
     name = n;
     address = add;
     nextRestaurantId++;
  }

  ~Restaurant(){
     cout<<"Destroying the Restaurant with id "<<id<<" and name "<<name<<endl;
      menu.clear();
  }
   
  string getName(){
   return name;
  }
  string setName(string& nam){
   name = nam;
  }
  string getAddress(){
   return address;
  }
  string setAddress(string& add){
     address = add;
  }
  void addItemInMenu(MenuItem* item){
    menu.push_back(item);
  }

  const vector<MenuItem*> getMenu(){
    return menu;
  }
};

int Restaurant::nextRestaurantId = 1;

int main(){

}

#endif