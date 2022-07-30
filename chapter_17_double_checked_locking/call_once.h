#ifndef CALL_ONCE_H
#define CALL_ONCE_H

#include <iostream>

// Header for std::once_flag and std::call_once
#include <mutex>

// Global object to store synchronization data
// (Could also be static member of Singleton)
std::once_flag single_flag;

class Singleton {
    // Private static member
    static Singleton *single;
public:
    // Static member function which
    // returns a Singleton object
    // This is the only way to get a Singleton
    static Singleton* get_singleton()
    {
        std::call_once(single_flag, []() {
        // Create the object
        single = new Singleton;
    });

        return single; 
    }   

protected:
    // The constructor is protected and
    // can only be called by a static member function
    Singleton()
    {
        std::cout << "Initializing singleton" << "\n";
    }
};

#endif //CALL_ONCE_H
