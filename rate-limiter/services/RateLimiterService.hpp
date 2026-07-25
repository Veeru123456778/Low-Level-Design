#pragma once 
#include<memory>
#include "../config/AlgoConfig.hpp"
#include "../strategies/RateLimitAlgo.hpp"

class RateLimiterService
{
private:
    /* data */
   RateLimitAlgo * rlalgo;
   RateLimiterConfig* cfg;

public:
    RateLimiterService(RateLimitAlgo* rlalgo, RateLimiterConfig* cfg){
        this->rlalgo = rlalgo;
        this->cfg = cfg;
    }
    ~RateLimiterService() = default;

    bool isAllowed(string user_id){
        if(!rlalgo){
            return false;
        }
        bool isAllow = rlalgo->processRequest(user_id,cfg);

        return isAllow;
    }
};

