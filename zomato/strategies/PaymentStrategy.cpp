#include<bits/stdc++.h>
using namespace std;

class PaymentStartegy{
  private:
   
  public:
  virtual void pay() = 0;

};

class UPIPayment:PaymentStartegy{
    public:
    void Pay(){
        cout<<"Payment is processing using UPI!!"<<endl;
    }
};

int main(){

}