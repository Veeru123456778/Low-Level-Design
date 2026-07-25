// #include<bits/stdc++.h>
// using namespace std;

// // Simple Factory
// class Burger{
//     public:
//     virtual void prepare() = 0;
//     virtual ~Burger(){}   // virtual constructor
// };

// class BasicBurger: public Burger{
//   public:
//   void prepare() override{
//       cout<<"Basic Burger is getting prepared...."<<endl;
//   }
// };

// class StandardBurger: public Burger{
//   public:
//   void prepare() override{
//       cout<<"Standard Burger is getting prepared...."<<endl;
//   }
// };

// class PremiumBurger: public Burger{
//   public:
//   void prepare() override{
//       cout<<"Premium Burger is getting prepared...."<<endl;
//   }
// };

// class QualityBurger: public Burger{
//     public:
//     void prepare() override{
//       cout<<"Quality Burger is getting prepared...."<<endl;
//     }
// };

// class BurgerFactory{
//   public:
  
//   Burger* createBurger(string& type){
//      if(type=="basic"){
//         return new BasicBurger();
//      }
//      else if(type=="standard"){
//         return new StandardBurger();
//      }
//      else if(type=="premium"){
//         return new PremiumBurger();
//      }
//      else if(type=="quality"){
//         return new QualityBurger();
//      }
//      else{
//         cout<<"Invalid burger type!"<<endl;
//         return nullptr;
//      }
//   }
// };


// int main(){
//      string type = "quality";
//     //  string type = "standard";
//      BurgerFactory* bFac = new BurgerFactory();

//      Burger* b = bFac->createBurger(type);
//      b->prepare();
// }



// //Factory Method
// #include<bits/stdc++.h>
// using namespace std;


// class Burger{
//     public:
//     virtual void prepare() = 0;
//     virtual ~Burger(){}   // virtual constructor
// };

// class BasicBurger: public Burger{
//   public:
//   void prepare() override{
//       cout<<"Basic Burger is getting prepared...."<<endl;
//   }
// };

// class StandardBurger: public Burger{
//   public:
//   void prepare() override{
//       cout<<"Standard Burger is getting prepared...."<<endl;
//   }
// };

// class PremiumBurger: public Burger{
//   public:
//   void prepare() override{
//       cout<<"Premium Burger is getting prepared...."<<endl;
//   }
// };

// class WheatBasicBurger: public Burger{
//     public:
//     void prepare() override{
//       cout<<"WheatBasic Burger is getting prepared...."<<endl;
//     }
// };
// class WheatStandardBurger: public Burger{
//     public:
//     void prepare() override{
//       cout<<"Wheat Standard Burger is getting prepared...."<<endl;
//     }
// };

// class WheatPremiumBurger: public Burger{
//     public:
//     void prepare() override{
//       cout<<"Wheat Premium Burger is getting prepared...."<<endl;
//     }
// };


// class BurgerFactory{
//    public:
//    virtual Burger* createBurger(string& type) = 0;
// };

// class SinghBurger: public BurgerFactory{
//   public:
//   Burger* createBurger(string& type){
//      if(type=="basic"){
//         return new BasicBurger();
//      }
//      else if(type=="standard"){
//         return new StandardBurger();
//      }
//      else if(type=="premium"){
//         return new PremiumBurger();
//      }
//      else{
//         cout<<"Invalid burger type!"<<endl;
//         return nullptr;
//      }
//   }
// };

// class KingBurger: public BurgerFactory{
//   public:
//   Burger* createBurger(string& type){
//      if(type=="basic"){
//         return new WheatBasicBurger();
//      }
//      else if(type=="standard"){
//         return new WheatStandardBurger();
//      }
//      else if(type=="premium"){
//         return new WheatPremiumBurger();
//      }
//      else{
//         cout<<"Invalid burger type!"<<endl;
//         return nullptr;
//      }
//   }
// };

// int main(){
//     BurgerFactory* bfc = new SinghBurger();
//     string type = "premium";
//     Burger* b = bfc->createBurger(type);
//     b->prepare();
// }



// Abstract Factory Method -> Ek factory ek se jada type k objects bnaye-> Ex: Burger and Dosa


//Factory Method
#include<bits/stdc++.h>
using namespace std;

class Dosa{
   public:
   virtual void 
};

class Burger{
    public:
    virtual void prepare() = 0;
    virtual ~Burger(){}   // virtual constructor
};

class BasicBurger: public Burger{
  public:
  void prepare() override{
      cout<<"Basic Burger is getting prepared...."<<endl;
  }
};

class StandardBurger: public Burger{
  public:
  void prepare() override{
      cout<<"Standard Burger is getting prepared...."<<endl;
  }
};

class PremiumBurger: public Burger{
  public:
  void prepare() override{
      cout<<"Premium Burger is getting prepared...."<<endl;
  }
};

class WheatBasicBurger: public Burger{
    public:
    void prepare() override{
      cout<<"WheatBasic Burger is getting prepared...."<<endl;
    }
};
class WheatStandardBurger: public Burger{
    public:
    void prepare() override{
      cout<<"Wheat Standard Burger is getting prepared...."<<endl;
    }
};

class WheatPremiumBurger: public Burger{
    public:
    void prepare() override{
      cout<<"Wheat Premium Burger is getting prepared...."<<endl;
    }
};


class BurgerFactory{
   public:
   virtual Burger* createBurger(string& type) = 0;
};

class SinghBurger: public BurgerFactory{
  public:
  Burger* createBurger(string& type){
     if(type=="basic"){
        return new BasicBurger();
     }
     else if(type=="standard"){
        return new StandardBurger();
     }
     else if(type=="premium"){
        return new PremiumBurger();
     }
     else{
        cout<<"Invalid burger type!"<<endl;
        return nullptr;
     }
  }
};

class KingBurger: public BurgerFactory{
  public:
  Burger* createBurger(string& type){
     if(type=="basic"){
        return new WheatBasicBurger();
     }
     else if(type=="standard"){
        return new WheatStandardBurger();
     }
     else if(type=="premium"){
        return new WheatPremiumBurger();
     }
     else{
        cout<<"Invalid burger type!"<<endl;
        return nullptr;
     }
  }
};

int main(){
    BurgerFactory* bfc = new SinghBurger();
    string type = "premium";
    Burger* b = bfc->createBurger(type);
    b->prepare();
}