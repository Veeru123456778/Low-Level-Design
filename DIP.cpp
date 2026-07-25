#include<bits/stdc++.h>
using namespace std;

class Persistence{
   public:
   virtual void save() = 0; 
};

class SaveToMongo: public Persistence{
    public:
    void save() override{
        cout<<"Saved to MongoDB successfully!!"<<endl;
    }
};

class SaveToSQL: public Persistence{
    public:
    void save() override{
        cout<<"Saved to SQL successfully!!"<<endl;
    }
};
class SaveToCassandra: public Persistence{
    public:
    void save() override{
        cout<<"Saved to Cassandra successfully!!"<<endl;
    }
};

class UserService{
   Persistence* p;
   public:
   UserService(Persistence* pInput){
     this->p = pInput;
   }
   void save(){
      p->save();
   }
};

int main(){
   Persistence* sql = new SaveToSQL();
   Persistence* mongo = new SaveToMongo();
   Persistence* cassandra = new SaveToCassandra();

   UserService* user = new UserService(sql);
   user->save();
   UserService* user2 = new UserService(mongo);
   user2->save();
   UserService* user3 = new UserService(cassandra);
   user3->save();
}