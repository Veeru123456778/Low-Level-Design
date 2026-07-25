// Ek object h or ham chahte h ki hum use dynamically change kar ske runtime pe for Ex: Agar hm do_something() function ko call kre or vo de "I did something" to hm chahte h ki hum use runtime p change kar ske, Ex: "I did something great!!"

// Hm inheritence use kar skte h or function ko override krke runtime p change kar skte h (Usi ka constructor call kao jo output m chahiye) par lekin hmne pdha h ki inheritence id bad (Multiple hierarchy create krta h ) so hm decorator design pattern ka use krenge

#include<bits/stdc++.h>
using namespace std;

class ICharacter{
   public:
   virtual string getAbilities() = 0;
   virtual ~ICharacter(){}
};

class Mario:public ICharacter{
   public:
   string getAbilities(){
     return "Mario"; 
   }
};

class Decorator: public ICharacter{
   protected:
   ICharacter* ch;
   public:
   Decorator(ICharacter* c){
      ch = c;
   }
};

class HeightUpDec:public Decorator{
   public:
   HeightUpDec(ICharacter* c):Decorator(c){
   // Star Power Object
   }
   string getAbilities(){
      return ch->getAbilities()+"With Height Up ";
   }
};


class StarPowerDec:public Decorator{
    public:
   StarPowerDec(ICharacter* c):Decorator(c){
    // Gun Power object
   } 
   string getAbilities(){
      return ch->getAbilities()+"With Star Power ";
   }
};

class GunPowerDec: public Decorator{
public:
   GunPowerDec(ICharacter* c):Decorator(c){
    // Mario object
   }
   string getAbilities(){
      return ch->getAbilities()+"With Gun Power ";
   }
};


int main(){
   ICharacter* mario = new HeightUpDec(new GunPowerDec(new Mario()));
   cout<<mario->getAbilities()<<endl;
}