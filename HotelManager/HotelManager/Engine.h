#pragma once
#include "RoomsController.h"
#include "ReservationsController.h"
#include "CloseRoomsController.h"

class Engine {
public:
    // This is how clients can access the single instance
    static Engine* getInstance();

    void run();
    void setValue(int val) { value_ = val; }
    int  getValue() { return(value_); }

protected:
    int value_;

private:
    void printCommands();
    static Engine* inst_;   // The one, single instance
    Engine();// private constructor
    Engine(const Engine&);
    Engine& operator=(const Engine&) = delete;
};
