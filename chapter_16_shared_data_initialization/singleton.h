#ifndef SINGLETON_H
#define SINGLETON_H

#include <iostream>

class Singleton {
    // Private static member
    static Singleton *single;
public:
    // Static member function which
    // returns a Singleton object
    // This is the only way to get a Singleton
    static Singleton* get_singleton()
    {
        // If the member object does not already exist
        if (single == 0) {
            // Create the object
            single = new Singleton;
        }
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

#endif //SINGLETON_H
