#pragma once
#include <string>
#include <vector>
#include <iostream>
#include "kernel/Kernel.h"
#include "kernel/MessageBus.h"

class Shell {
public:
    Shell(Kernel& kernel, MessageBus& bus);

    // Called periodically as a task
    void tick();

private:
    Kernel& kernel_;
    MessageBus& bus_;

    std::vector<std::string> tokenize(const std::string& line);
    void handleCommand(const std::vector<std::string>& tokens);
};
