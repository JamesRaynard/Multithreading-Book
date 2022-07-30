#ifndef SINGLETON_ATOMIC_H
#define SINGLETON_ATOMIC_H

#include <iostream>
#include <mutex>
#include <atomic>

std::mutex mut;

class Singleton {
    // Private static member
    static std::atomic<Singleton *> single;
public:
    // Static member function which
    // returns a Singleton object
    // This is the only way to get a Singleton
    static Singleton* get_singleton()
    {
        // If the member object does not already exist
        if (single == nullptr) {
            std::lock_guard<std::mutex> lg(mut);
            // If the member object does not already exist
            if (single == nullptr) {
                // Create it
                single = new Singleton;
            }
        }
        return single; 
    }

protected:
    // The constructor is protected and
    // can only be called by a static member function
    Singleton()
    {
       std::cout << "Initializing singleton\n";
    }
};

#endif //SINGLETON_ATOMIC_H
