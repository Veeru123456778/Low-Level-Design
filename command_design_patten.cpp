// Ham Source or Reciever ko directly communicate nhi krate blki ham unke beech me ek aur object (Ex: Command) introduce kra dete h jisse ki source or reciever loosely coupled ho jaye
// Source -----> Command ------> Reciever
// Source <------ Command <------ Reciever

// Ex: Smart Home Automation System
// Advantage of Command design pattern -> like we can also undo any command that we have executed previously

#include<bits/stdc++.h>
using namespace std;


class ICommand{
   public:
   virtual void execute() = 0;
   virtual void undo() = 0;
   virtual ~ICommand(){}
};


class RemoteControl{
    vector<ICommand*> commands;
    vector<bool> isButtonOn;
    static size_t numButtons;
    public:

    RemoteControl(){
      commands.resize(numButtons,nullptr);
      isButtonOn.resize(numButtons,false);
    }

    void setCommand(size_t idx,ICommand* c){
        if( idx<numButtons){
          if(commands[idx]!=nullptr){
            delete commands[idx];
          }
          commands[idx] = c;
          isButtonOn[idx] = false;
        }
    }

    void pressButton(size_t idx){
      if(idx<numButtons && commands[idx]!=nullptr){
            if(isButtonOn[idx]){
               commands[idx]->undo();
            }
            else{
               commands[idx]->execute();
            }
            isButtonOn[idx] = !isButtonOn[idx];
      }
      else{
         cout<<"Command not set for this Index!!"<<endl;
      }
    }

    ~RemoteControl(){
       for(size_t i=0;i<4;i++){
         if(commands[i]!=nullptr){
            delete commands[i];
         }
       }
    }
};

size_t RemoteControl::numButtons = 4;

class Light{
  public:
  void on(){
     cout<<"Light is on now!!"<<endl;
  }
  void off(){
     cout<<"Light is off now!!"<<endl;
  }

};

class LightCommand:public ICommand{
    Light* light;
    public:
    LightCommand(Light* l){
        light = l;
    }
    void execute(){
         light->on();
    }
    void undo(){
         light->off();
    }
};


int main(){
    Light* light = new Light();
    ICommand* lightCommand = new LightCommand(light);
    RemoteControl* remote = new RemoteControl();
    remote->setCommand(0,lightCommand);
    remote->pressButton(0);
    remote->pressButton(0);
    remote->pressButton(2);
}