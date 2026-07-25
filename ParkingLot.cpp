#include<bits/stdc++.h>
using namespace std;

class Vehicle{
    public:
    bool isEntered;
    string vehicle_number;
    virtual void enterIntoParking() = 0;
    virtual void exitFromParking() = 0;
};

class MotorCycle:public Vehicle{
   public:
   MotorCycle(string& vNum){
    vehicle_number = vNum;
    isEntered = false;
   }
   
   void enterIntoParking(){

   }

   void exitFromParking(){
    
   }
};
class Car:public Vehicle{
   public:
   Car(string& vNum){
    vehicle_number = vNum;
   }

   void enterIntoParking(){

   }

   void exitFromParking(){
    
   }
};
class Bus:public Vehicle{
   public:
   Bus(string& vNum){
    vehicle_number = vNum;
   }

   void enterIntoParking(){

   }

   void exitFromParking(){
    
   }
};

class ParkingSlot{
    private:
    Vehicle* vehicle;
    bool isOccupied;
    public:
    static int nextSlotId;
    int slotId;

    ParkingSlot(){
       slotId = ++nextSlotId;
       vehicle = nullptr;
       isOccupied = false;
    }
};

int ParkingSlot::nextSlotId = 0;

class MotorCycleSlot:public ParkingSlot{

};
class CarSlot:public ParkingSlot{

};
class BusSlot:public ParkingSlot{

};

class ParkingLevel{
   private:
   unordered_set<ParkingSlot*> parkingSlotsInLevel;
   int parkingLevelId = 0;
   public:
   static int nextParkingLevelId;

   ParkingLevel(){
       parkingLevelId = ++nextParkingLevelId;
   }
   void addParkingSlot(ParkingSlot* ps){
       parkingSlotsInLevel.insert(ps);
   }
   void removeParkingSlot(ParkingSlot* ps){
      parkingSlotsInLevel.erase(ps);
   }
};

int ParkingLevel::nextParkingLevelId = 0;

class ParkingLot{
   private:
   unordered_set<ParkingLevel*> parkingLevelsInLot;
   public:
   void addParkingLevel(){
      ParkingLevel* pl = new ParkingLevel();
      parkingLevelsInLot.insert(pl);
   }
   void removeParkingLevel(ParkingLevel* pl){
      parkingLevelsInLot.erase(pl);
   }
};

class Admin{
   private:
   string name;
   ParkingLot* pLot;
   mutex m;
   public:
   static Admin* adminInstance;

   Admin* getInstance(){
     if(adminInstance==nullptr){
        lock_guard<mutex> lock(m);
        if(adminInstance==nullptr){
        adminInstance = new Admin();
        }
     }
     return adminInstance;
   }

   void viewStatus(){
      
   }

   void addParkingLevel(){
      pLot->addParkingLevel();
   }
   
   
};

Admin* Admin::adminInstance = nullptr;

int main(){

}