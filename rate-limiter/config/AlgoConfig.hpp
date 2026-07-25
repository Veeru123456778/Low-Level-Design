#pragma once 

class RateLimiterConfig{
    public:

    virtual ~RateLimiterConfig() = default;

};


class TokenBucketConfig : public RateLimiterConfig{
    private:

    public:

    long long max_capacity;
    long long prefill_rate;
    long long window_size;

    TokenBucketConfig(long long max_capacity,long long prefill_rate, long long window_size){
         this->max_capacity = max_capacity;
         this->prefill_rate = prefill_rate;
         this->window_size = window_size;
    }

};