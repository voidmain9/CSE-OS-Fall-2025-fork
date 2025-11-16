#pragma once
#include "Driver.h"
#include "kernel/MessageBus.h"
#include <iostream>

class ConsoleDriver : public Driver {
public:
    ConsoleDriver(MessageBus& bus)
        : Driver("ConsoleDriver"), bus_(bus) {}

    void init() override {
        std::cout << "[ConsoleDriver] Initialized.\n";
        bus_.publish({"log", "[ConsoleDriver] Initialized"});
    }

private:
    MessageBus& bus_;
};
