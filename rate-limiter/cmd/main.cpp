#include<iostream>
#include<string>
#include "../strategies/TokenBucketAlgo.hpp"
#include "../config/AlgoConfig.hpp"
#include "../services/RateLimiterService.hpp"

using namespace std;


int main()  {

	RateLimiterConfig* loginConfig = new TokenBucketConfig(100LL,20LL,10LL);

    RateLimitAlgo* algoengine = new TokenBucketAlgo();

    RateLimiterService* rlsvc = new RateLimiterService(algoengine,loginConfig);

    string user_id = "user_123";

    for (int i = 0; i < 7; i++) {
        bool val = rlsvc->isAllowed(user_id);
        if (val) {
            cout << "Request " << i + 1 << " Allowed\n";
        } else {
            cout << "Request " << i + 1 << " Not Allowed\n";
        }
    }

   delete loginConfig;
   delete algoengine;
   delete rlsvc;
   return 0;
}