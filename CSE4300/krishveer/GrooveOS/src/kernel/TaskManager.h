#pragma once

#include <vector>
#include <string>
#include <functional>
#include <chrono>

#include "MessageBus.h"

struct Task {
    int id; // unique task ID
    std::string name;
    std::function<void()> callback;
    std::uint32_t period_ms;
    std::chrono::steady_clock::time_point next_run;
};

class TaskManager {
public:
    explicit TaskManager(MessageBus& bus);

    // Add a new scheduled task
    void addTask(const std::string& name,
                 std::uint32_t period_ms,
                 std::function<void()> cb);

    // Called from Kernel::run() to execute any due tasks
    void runOnce();

    // For shell/diagnostics
    const std::vector<Task>& tasks() const {
        return tasks_;
    }

private:
    std::vector<Task> tasks_;
    MessageBus& bus_; // used for logging, notifications, etc.
};
