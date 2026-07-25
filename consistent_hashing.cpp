#include<iostream>
#include<string>
#include<vector>
#include<map>
#include<time.h>
#include<thread>
#include<chrono>

using namespace std;

// Every server will implement this class

class Server{
  private:

  public:
  string name;

  Server(string n){
      name = n;
  }

  void processRequest(string req_id){
      cout<<"process the request on server "<<this->name<<" with request id: "<<req_id<<endl;
  }
};

class ConsistentHashing{
    // i have an array of the servers denoting -[10,50,90] means 0th server is at 10 and so on

    map<size_t,Server*> ring;
    int numVirtualNodes; 

    size_t hashFunction(string val){
        hash<string> hasher;
        return hasher(val);
    }

    public:

    ConsistentHashing(int numNodes){
        numVirtualNodes = numNodes;
    }

    void addAServer(Server* server){
        for(int i=0;i<numVirtualNodes;i++){
            string key = server->name+"#vn"+to_string(i);

            size_t pos = hashFunction(key);
            ring[pos] = server;
        }
    }

    void removeAServer(Server* server){
        for(int i=0;i<numVirtualNodes;i++){
            string key = server->name+"#vn"+to_string(i);
            size_t hashVal = hashFunction(key);
            ring.erase(hashVal);
        }
    }

    void processRequest(string req_id){

        if(ring.empty()){
          return;
        }

        size_t hashValue = hashFunction(req_id);
       
        // lower bound of the hasValue

        auto it = ring.lower_bound(hashValue);

        if(it==ring.end()){
            it = ring.begin();
        }

        // Now idx will consist of the index of the server now we can map this index to the instance of the server so that we can process the request to that specific server....

        // Forward Request to the <idx> server 
        
        it->second->processRequest(req_id); // we have just send the request to the respective server

    }
};

int main(){
    ConsistentHashing* ConsistentHashingEngine = new ConsistentHashing(50);

    Server* svr1 =  new Server("Server A");
    
    Server* svr2 = new Server("Server B");

    ConsistentHashingEngine->addAServer(svr1);
    
    ConsistentHashingEngine->addAServer(svr2);

    int cnt = 1;

    while (true)
    {
        string req_id = "req"+to_string(cnt);
        ConsistentHashingEngine->processRequest(req_id);
        cnt++;
        this_thread::sleep_for(chrono::seconds(3));
    }
    
}