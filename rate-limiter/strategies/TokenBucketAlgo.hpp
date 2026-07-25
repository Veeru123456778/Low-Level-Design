#pragma once 
#include<unordered_map>
#include<string>
#include<chrono>
#include<algorithm>
#include<mutex>
#include "RateLimitAlgo.hpp"
#include "../config/AlgoConfig.hpp"

using namespace std;

class TokenBucketAlgo : public RateLimitAlgo
{
private:
    /* data */
    // map of user_id with the token_balance and for last_prefill_timestamp
    mutex mtx;
    unordered_map<string,int> token_balance;
    unordered_map<string,long long> last_prefill_timestamp; // user_id with epoch timestamp
    
public:
    TokenBucketAlgo();
    ~TokenBucketAlgo();
    
    auto getCurrentTime(){
        auto now = std::chrono::system_clock::now();
        
        // Convert the time to seconds since epoch
        auto epochSeconds = std::chrono::duration_cast<std::chrono::seconds>(
                                now.time_since_epoch()
                            ).count();

        return epochSeconds;
    }


    bool processRequest(string user_id,RateLimiterConfig *config){
      
      lock_guard<mutex> lock(mtx);

    //   const TokenBucketConfig* bucketConfig = dynamic_cast<const TokenBucketConfig*>(config);

      const TokenBucketConfig* bucketConfig = dynamic_cast<const TokenBucketConfig*>(config);

      
      long long prefill_rate = bucketConfig->prefill_rate;
      long long current_timestamp = getCurrentTime();
      long long window_size = bucketConfig->window_size;
      long long max_capacity = bucketConfig->max_capacity;
      

      // max_capacity should also be taken into consideration - if  token_balance[user_id]+prefill_rate exceeds max_capacity then max_capacity needs to be taken...
      
      if(last_prefill_timestamp.find(user_id)==last_prefill_timestamp.end()){
        token_balance[user_id] = max_capacity;
        last_prefill_timestamp[user_id] = current_timestamp;
      }
      else{
        long long lstPrefillT = last_prefill_timestamp[user_id];
        
        if((current_timestamp-lstPrefillT)>=window_size){
            long long windows = (current_timestamp-lstPrefillT)/window_size;
            token_balance[user_id] = min(max_capacity, token_balance[user_id]+(windows*prefill_rate)); // number of tokens per window_size
            last_prefill_timestamp[user_id] = current_timestamp;
        }
      }

      if(token_balance[user_id]>0){
         token_balance[user_id]--;
         // call to the main service or we can return true to the rate limiter service and it will then forwards the request
         return true;
      }

      return false;
    }

};

