#include<bits/stdc++.h>
using namespace std;

class Parent{
    public:
    virtual void getValue() noexcept(false){
        throw logic_error("Exception occurs: logic_error");
    }
};
class Child:public Parent{
    public:
    void getValue() noexcept(false) override{
      throw out_of_range("Exception occurs: Out_Of_range");
    }
};

class Client{
    Parent* p;
    public:
    Client(Parent* par){
       this->p = par;
    }
    void takeValue(){
        try{
            p->getValue();
        }
        catch(logic_error& e){
           cout<<e.what()<<endl;
        }
    }
};

int main(){
     Parent* p = new Parent();
     Child* ch = new Child();

     Client *c = new Client(p);
     Client *c2 = new Client(ch);
     c->takeValue();
     c2->takeValue();

}