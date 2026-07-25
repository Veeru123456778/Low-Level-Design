#pragma once 
#include<string>
#include "../config/AlgoConfig.hpp"

using namespace std;

class RateLimitAlgo{
    private:
    // data here
    
    public:
      virtual ~RateLimitAlgo() = default;
      
      virtual bool processRequest(string user_id, RateLimiterConfig *config); // it will process the request and give response
};