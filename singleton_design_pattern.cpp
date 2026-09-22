#include<bits/stdc++.h>
using namespace std;

// Singleton Design Pattern: It is only for the 

// Yha problem h ki ye thread safe nhi h , multiple threads hmari application ko ek saath run kar skti h
class Singleton{
    private:
    static Singleton* instance; // for java we can write this { = nullptr } directly
    static mutex m;

    Singleton(){
        cout<<"Singleton class object created!!"<<endl;
    }    
    public:

    // static Singleton* getInstance(){
    //     // Iss part ko critical section ki treh lena chahiye no two threads can create this objects simultaneouly
    //   if(instance==nullptr){
    //     instance = new Singleton();
    //   }
    //   return instance;
    // }

    // Thread Safe 

    static Singleton* getInstance(){
      if(instance==nullptr){
        lock_guard<mutex> lock(m); // abb is pe lock laggya ab iske baad wale area me ek hi thread enter kar payegi or hmne lock andar isliye lagaya kyuki lock ek expensive operation h or hme use km se kam use krna h....

        if(instance==nullptr){ // But we need to check it again because suppose two threads if(instance==nullptr)
 //checks this condition and if it gets true for both then both will aquire lock one by one so we need to again check this condition because only 1st thread can create a fresh new object
        instance = new Singleton();
        }
      }
      return instance;
    }

};


Singleton* Singleton::instance = nullptr; // C++ me aise assign krna padega java me hm jidhar declare kra tha class me vhi p assign kr skte h


int main(){
   Singleton* obj = Singleton::getInstance();
   Singleton* anotherObj = Singleton::getInstance();

   cout<<(obj==anotherObj)<<endl;
}


// Hmm ek aur method use kar skte h that is eager initialization means main (application run hone se phle hi object initialize krde) using 
// Singleton* Singleton::instance = new Singleton(); - like this 
// But iske disadvantages h ki agar object bhot heavy hua build krne me to vo application se phle object create hojaega or falty me memory khayega.