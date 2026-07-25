// Features :->
// Plug and play model -> we can intergrate it with any app that has notification service
// Extendible: SMS, Whatsapp,email
// Notification content dynamic like we can add header/ footer at runtime dynamically
// Store all notifications / logging -> in a file or somewhere

// #include<bits/stdc++.h>
// using namespace std;

// class NotificationService;
// class INotificationObservalble;


// class INotification{
//     public:
//     virtual string getNotification() = 0;
//     ~INotification(){}
// };

// class SimpleNotification:public INotification{
//      string text;
//      public:
//      SimpleNotification(string& notification){
//         text = notification;
//      }
//      string getNotification(){
//         return text;
//      }
// };

// class NotificationDecorator: public INotification{
//   protected:
//     INotification* notification;
//   public:
//   NotificationDecorator(INotification* n){
//       notification = n;
//   }  
// };

// class AddTimeStampDecorator:public NotificationDecorator{
// //    INotification* notification;
//    public:
//    AddTimeStampDecorator(INotification* n):NotificationDecorator(n){
//     // notification = n;
//    }
   
//    string getNotification(){
//       return notification->getNotification()+" "+"Time: 10:20AM";
//    }
// };


// class SignatureDecorator:public NotificationDecorator{
// //    INotification* notification;
//    public:
//    SignatureDecorator(INotification* n):NotificationDecorator(n){
//     // notification = n;
//    }
   
//    string getNotification(){
//       return notification->getNotification()+" "+"This is a signature generated automatically!!";
//    }
// };

// class INotificationObserver{
//    public:
//    virtual void update() = 0;
// };

// class NotificationObserverLogger:public INotificationObserver{
//    INotification* notification;
//    INotificationObservalble* observable;
//    public:
//    NotificationObserverLogger(INotification* n){
//       notification = n;
//     this->observable = NotificationService::getInstance()->getObservable();
//     observable->addObserver(this);
//    }
 
//    void update(){
//      string notificationContent = notification->getNotification();
//      observable->setNotification(notification);
//    }   
// };


//  class INotificationStrategy{
//     public:
//     virtual void sendNotification(string& content) = 0;
//  };


//  class SMSNotificationStrategy:public INotificationStrategy{
//    public:
//    void sendNotification(string& content){
//        cout<<"Notification sent via SMS having content: "<<content<<endl;
//    }
//  };


//  class EmailNotificationStrategy:public INotificationStrategy{
//    public:
//    void sendNotification(string& content){
//        cout<<"Notification sent via Email having content: "<<content<<endl;
//    }
//  };


//  class WhatsAppNotificationStrategy:public INotificationStrategy{
//    public:
//    void sendNotification(string& content){
//        cout<<"Notification sent via Whatsapp having content: "<<content<<endl;
//    }
//  };


//  class INotificationObservalble{
//     public:
//     virtual void notify() = 0;
//     virtual void addObserver(INotificationObserver* o) = 0;
//     virtual void removeObserver(INotificationObserver* o) = 0;
//     virtual void setNotification(INotification* n) = 0;
//     virtual string getNotification() = 0;
//  };




//  class NotificationObservable:public INotificationObservalble{
//      unordered_set<INotificationObserver*> observerList;
//      INotification* notification;

//      public:
//      void addObserver(INotificationObserver* o){
//         if(observerList.find(o)==observerList.end()){
//         observerList.insert(o);
//         }
//      }
//      void removeObserver(INotificationObserver* o){
//         if(observerList.find(o)!=observerList.end()){
//             observerList.erase(o);
//         }
//      }
//      void notify(){
//         for(auto& o:observerList){
//             o->update();
//         }
//      }

//      void setNotification(INotification* n){
//         notification = n;
//         notify();
//      }

//      string getNotification(){
//         return notification->getNotification();
//      }
//  };




//  class NotificationEngine:public INotificationObserver{
//   vector<INotificationStrategy*> strategyList;
//   INotificationObservalble* observable;
  
//   public:
//   NotificationEngine(){
//     this->observable = NotificationService::getInstance()->getObservable();
//     observable->addObserver(this);
//   }

//   void update(){
//      for(auto& strategy:strategyList){
//         string content = observable->getNotification();
//         strategy->sendNotification(content);
//      }
//   }
//     void setObservable(INotificationObservalble* obs) {
//         observable = obs;
//     }
//   void addNotificationStrategy(INotificationStrategy* strategy){
//     strategyList.push_back(strategy);
//   }
// };
 



// class NotificationService{
//    private:
//    vector<INotification*> notifications; // need to store all notifications!!
//    INotificationObservalble* observable;
//    static mutex m;
//    static NotificationService* instance;
//    NotificationService(){
//     observable = new NotificationObservable();
//    }

//    public:
//    static NotificationService* getInstance(){
//      if(instance==nullptr){
//         lock_guard<mutex> lock(m);
//         if(instance==nullptr){
//             instance = new NotificationService();
//         }
//      }
//      return instance;
//    }

//    INotificationObservalble* getObservable(){
//     return observable;
//    }

//    void sendNotification(INotification* n){
//      notifications.push_back(n);
//      observable->setNotification(n);
//    }
// };

// NotificationService* NotificationService::instance = nullptr;
// mutex NotificationService::m;

// int main(){
    
//   NotificationService* notification_service = NotificationService::getInstance();
//   string notification = "Hi, your balance gets updated to Rs.100";
//   INotification* n = new SimpleNotification(notification);
//   n = new AddTimeStampDecorator(n);

//   INotificationStrategy* sms = new SMSNotificationStrategy();

//   NotificationEngine* varun = new NotificationEngine();
//     varun->addNotificationStrategy(sms);

// //   INotificationObservalble* Notification_Obs = notification_service->getObservable();
// //   varun->setObservable(Notification_Obs);  // <-- FIX
// //   Notification_Obs->addObserver(varun);

//   notification_service->sendNotification(n);

// }



#include <bits/stdc++.h>
using namespace std;

class NotificationService;
class INotificationObservable;

// Notification Interface
class INotification {
public:
    virtual string getNotification() = 0;
    virtual ~INotification() {}
};

// Simple Notification
class SimpleNotification : public INotification {
    string text;
public:
    SimpleNotification(const string& notification) : text(notification) {}
    string getNotification() override {
        return text;
    }
};

// Notification Decorator
class NotificationDecorator : public INotification {
protected:
    INotification* notification;
public:
    NotificationDecorator(INotification* n) : notification(n) {}
};

// Add Timestamp
class AddTimeStampDecorator : public NotificationDecorator {
public:
    AddTimeStampDecorator(INotification* n) : NotificationDecorator(n) {}
    string getNotification() override {
        return notification->getNotification() + " Time: 10:20AM";
    }
};

// Observer Interface
class INotificationObserver {
public:
    virtual void update() = 0;
    virtual ~INotificationObserver() {}
};

// Strategy Interface
class INotificationStrategy {
public:
    virtual void sendNotification(string& content) = 0;
    virtual ~INotificationStrategy() {}
};

// SMS Strategy
class SMSNotificationStrategy : public INotificationStrategy {
public:
    void sendNotification(string& content) override {
        cout << "Notification sent via SMS: " << content << endl;
    }
};

// Observable Interface
class INotificationObservable {
public:
    virtual void notify() = 0;
    virtual void addObserver(INotificationObserver* o) = 0;
    virtual void setNotification(INotification* n) = 0;
    virtual string getNotification() = 0;
    virtual ~INotificationObservable() {}
};

// Observable Implementation
class NotificationObservable : public INotificationObservable {
    unordered_set<INotificationObserver*> observers;
    INotification* notification = nullptr;
public:
    void addObserver(INotificationObserver* o) override {
        observers.insert(o);
    }
    void notify() override {
        for (auto& o : observers) o->update();
    }
    void setNotification(INotification* n) override {
        notification = n;
        notify();
    }
    string getNotification() override {
        return notification ? notification->getNotification() : "";
    }
};

// Notification Service (Singleton)
class NotificationService {
    vector<INotification*> notifications;
    INotificationObservable* observable;
    static NotificationService* instance;
    static mutex m;

    NotificationService() {
        observable = new NotificationObservable();
    }

public:
    static NotificationService* getInstance() {
        if (!instance) {
            lock_guard<mutex> lock(m);
            if (!instance) instance = new NotificationService();
        }
        return instance;
    }

    INotificationObservable* getObservable() { return observable; }

    void sendNotification(INotification* n) {
        notifications.push_back(n);
        observable->setNotification(n);
    }
};

NotificationService* NotificationService::instance = nullptr;
mutex NotificationService::m;

// Notification Engine
class NotificationEngine : public INotificationObserver {
    vector<INotificationStrategy*> strategies;
    INotificationObservable* observable;

public:
    NotificationEngine() {
        observable = NotificationService::getInstance()->getObservable();
        observable->addObserver(this);
    }

    void update() override {
        string content = observable->getNotification();
        for (auto& s : strategies) s->sendNotification(content);
    }

    void addNotificationStrategy(INotificationStrategy* strategy) {
        strategies.push_back(strategy);
    }
};

// Main
int main() {
    NotificationService* service = NotificationService::getInstance();

    string text = "Hi, your balance is Rs.100";
    INotification* n = new SimpleNotification(text);
    n = new AddTimeStampDecorator(n);

    INotificationStrategy* sms = new SMSNotificationStrategy();
    NotificationEngine* engine = new NotificationEngine();
    engine->addNotificationStrategy(sms);

    service->sendNotification(n);

    return 0;
}
