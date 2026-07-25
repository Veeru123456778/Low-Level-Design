#include<bits/stdc++.h>
using namespace std;

//Interface or Abstract class or Family of Strategy Algorithms
class Talkable{
   public:
   virtual void talk() = 0;
};

class Walkable{
    public:
    virtual void walk() = 0;
};

class Flyable{
  public:
  virtual void fly() = 0;
};

class NormalTalk : public Talkable{
   public:
   void talk(){
    cout<<"Robot is talking..."<<endl;
   }
};

class NoTalk: public Talkable{
    public:
    void talk(){
        cout<<"Robot will not talk...."<<endl;
    }
};

class NormalWalk: public Walkable{
  public:
  void walk(){
     cout<<"Robot is walking..."<<endl;
  }
};

class NoWalk : public Walkable{
  public:
  void walk(){
    cout<<"Robot will not walk...."<<endl;
  }
};

class NormalFly: public Flyable{
   public:
   void fly(){
    cout<<"Robot is flying..."<<endl;
   }
};

class NoFly: public Flyable{
   public:
   void fly(){
     cout<<"Robot will not fly...."<<endl;
   }
};



class Robot{
  Talkable* t;
  Walkable* w;
  Flyable* f;
  public:
  Robot(Talkable* ta,Walkable* wa,Flyable* fl){
      this->t = ta;
      this->w = wa;
      this->f = fl;
  }

    void walk(){
        w->walk();
    }
    void talk(){
        t->talk();
    }
    void fly(){
        f->fly();
    }

    virtual void projection() = 0;
};

class CompanionRobot: public Robot{
  public:
  CompanionRobot(Talkable* ta,Walkable* wa,Flyable* fa): Robot(ta,wa,fa){
     
  }

  void projection(){
    cout<<"Displaying friendly companion features...."<<endl;
  }
};

int main(){
    Robot* campRobot  = new CompanionRobot(new NormalTalk(),new NormalWalk(),new NoFly());
    campRobot->fly();
    campRobot->talk();
    campRobot->walk();
    campRobot->projection();
}