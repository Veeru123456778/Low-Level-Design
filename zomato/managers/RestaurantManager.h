#include<bits/stdc++.h>
#include <zomato/models/Restaurant.h>
using namespace std;

class RestaurantManager{
    private:
    vector<Restaurant*> all_restaurants;
    static RestaurantManager* instance;
    
    RestaurantManager(){

    }
    public:

    static RestaurantManager* getInstance(){
         if(instance==nullptr){
           instance = new RestaurantManager();
         }
         return instance;
    }
    void addRestaurant(Restaurant* res){
        all_restaurants.push_back(res);
    }
    
    vector<Restaurant*> serachRestaurantByLocation(string location){
        transform(location.begin(),location.end(),location.begin(),::tolower);
        vector<Restaurant*> matchedRestaurants;
        for(auto& r:all_restaurants){
            string resAdd = r->getAddress();
            transform(resAdd.begin(),resAdd.end(),resAdd.begin(),::tolower);
            if(resAdd==location){
               matchedRestaurants.push_back(r);
            }
        }
        return matchedRestaurants;
    }
};

RestaurantManager* RestaurantManager::instance = nullptr;


int main(){

}