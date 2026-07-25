#include<bits/stdc++.h>
using namespace std;

// Jb bhi hm ek channel subscribe krte h to hme notification aati h to vo notification kaise aati h,kaise hmara youtube account or vo channel interact krte h?? -> vo hm seekhenge observer pattern se

// class IObserver{
//    public:
//    virtual void update() = 0;
// };

// class ConcreteObserver:public IObserver{
//     IObservable* obs;
//     void update(){
//        obs = obs->getValue();
//        return;
//     }

// };


// class IObservable{
//    public:
//    unordered_set<IObserver*> observerList;
//    IObservable* observable;
//    virtual void addObserver(IObserver* ob) = 0;
//    virtual void removeObserver() = 0;
//    virtual IObservable* getValue() = 0;
// };

// class ConcreteObservable:public IObservable{
//    public:
//    ConcreteObservable(){
//     observable = nullptr;
//    }
//    void addObserver(IObserver* ob){
//       observerList.insert(ob);
//    }
//    void removeObserver(IObserver* ob){
//       observerList.erase(ob);
//    }
//    IObservable* getValue(){
//     return observable;
//    }
// };


// int main(){
    
// }



class ISubscriber{
   public:
   virtual void update() = 0;
};


class IChannel{
  public:
  virtual void subscribe(ISubscriber* sub) = 0;
  virtual void unsubscribe(ISubscriber* sub) = 0;
  virtual void notifySubscribers() = 0;

};

class ConcreteChannel: public IChannel{
    private:
    unordered_set<ISubscriber*> listSubscribers;
    string name;
    string latestVideo;
    public:
    ConcreteChannel(string n){
       name = n;
    }
    void subscribe(ISubscriber* sub){
       listSubscribers.insert(sub);
    }
    void unsubscribe(ISubscriber* sub){
        listSubscribers.erase(sub);
    }

    void uploadVideo(string video){
      latestVideo = video;
      notifySubscribers();
    }

    void notifySubscribers(){
        for(auto& s:listSubscribers){
            s->update();
        }
    }
    string getName(){
        return name;
    }
    string getLatestVideo(){
        return latestVideo;
    }
};

class ConcreteSubscriber: public ISubscriber{
   ConcreteChannel* ch;
   string name;
   public:
   ConcreteSubscriber(string n,ConcreteChannel*& c){
     ch = c;
     name = n;
   }
   void update(){
    string video = ch->getLatestVideo();
    cout<<"Latest Video uploaded by Channel TO subscriber : "<<name<<" "<<ch->getName()<<"->"<<video<<endl;
   }
};



int main(){
    ConcreteChannel* channel = new ConcreteChannel("IIITIAN VARUN");

    ConcreteSubscriber* sub1 = new ConcreteSubscriber("Varun",channel);
    ConcreteSubscriber* sub2 = new ConcreteSubscriber("Rahul",channel);
    
    channel->subscribe(sub1);
    channel->subscribe(sub2);
    
    channel->uploadVideo("My first Vlog");
    
    channel->unsubscribe(sub1);

     channel->uploadVideo("My Second Vlog");
}