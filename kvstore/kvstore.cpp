#include <iostream>
#include <unordered_map>
#include <string>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <chrono>

using namespace std;

class KeyValueStore {
    unordered_map<string, pair<long long, string>> kvstore;
    unordered_map<string, long long> ttls;
    thread backgroundWorker;
    mutex mtx;
    condition_variable cv;
    bool stopSignal = false; // Flag to tell worker thread to exit

public:
    KeyValueStore() {
        backgroundWorker = thread(&KeyValueStore::backgroundRunner, this);
    }

    ~KeyValueStore() {
        {
            lock_guard<mutex> lock(mtx);
            stopSignal = true; // Signal thread to stop
        }
        cv.notify_all(); // Wake up background thread immediately

        if (backgroundWorker.joinable()) {
            backgroundWorker.join(); // Now joins cleanly in < 1 millisecond!
        }
    }

    void backgroundRunner() {
        while (true) {
            unique_lock<mutex> lock(mtx);

            // Wait 10 seconds OR until destructor signals stopSignal
            if (cv.wait_for(lock, chrono::seconds(10), [this]() { return stopSignal; })) {
                return; // Exit thread loop cleanly on shutdown
            }

            auto currentTime = chrono::system_clock::now().time_since_epoch();
            auto millSecCurrTime = chrono::duration_cast<chrono::milliseconds>(currentTime).count();

            // Safe iteration & deletion using explicit iterators
            for (auto it = kvstore.begin(); it != kvstore.end(); ) {
                string key = it->first;

                if (ttls[key] != -1 && (millSecCurrTime - it->second.first) >= ttls[key]) {
                    ttls.erase(key);
                    it = kvstore.erase(it); // Safe iterator removal!
                } else {
                    ++it;
                }
            }
        }
    }

    bool set(string key, string val, long long ttl = -1) {
        lock_guard<mutex> lock(mtx);
        
        auto duration = chrono::system_clock::now().time_since_epoch();
        long long now = chrono::duration_cast<chrono::milliseconds>(duration).count();

        kvstore[key] = {now, val};
        ttls[key] = ttl;

        return true;
    }

    string getKey(string key) {
        lock_guard<mutex> lock(mtx); // Lock MUST be first line!

        auto it = kvstore.find(key);
        if (it == kvstore.end()) {
            throw runtime_error("Key not found!");
        }

        // Optional Lazy Check: Expiry check at GET time
        if (ttls[key] != -1) {
            auto currentTime = chrono::system_clock::now().time_since_epoch();
            auto now = chrono::duration_cast<chrono::milliseconds>(currentTime).count();
            if ((now - it->second.first) >= ttls[key]) {
                kvstore.erase(it);
                ttls.erase(key);
                throw runtime_error("Key expired!");
            }
        }

        return it->second.second;
    }

    bool deleteKey(string key) {
        lock_guard<mutex> lock(mtx); // Lock MUST be first line!

        if (kvstore.find(key) == kvstore.end()) {
            return false;
        }

        kvstore.erase(key);
        ttls.erase(key);
        return true;
    }
};

int main() {
    KeyValueStore kv;

    kv.set("NameOne", "Varun", 1000); // Expires in 1000 ms (1 sec)

    cout << "Value: " << kv.getKey("NameOne") << endl;

    this_thread::sleep_for(chrono::milliseconds(1100));

    try {
        cout << kv.getKey("NameOne") << endl;
    } catch (const exception& e) {
        cout << e.what() << endl; // Prints "Key expired!"
    }
}