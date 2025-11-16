#include "kernel/TaskManager.h"
#include <iostream>
#include <sstream>

TaskManager::TaskManager(MessageBus& bus)
    : bus_(bus) {}

void TaskManager::addTask(const std::string& name,
                          std::uint32_t period_ms,
                          std::function<void()> cb) {
    static int nextId = 0;

    Task t{
        nextId++,
        name,
        std::move(cb),
        period_ms,
        std::chrono::steady_clock::now()
    };

    tasks_.push_back(t);

    std::cout << "[TaskManager] Added task: " << name
              << " (" << period_ms << "ms)\n";

    // Log via MessageBus instead of calling Kernel::instance()
    std::stringstream ss;
    ss << "Task added: " << name << " (" << period_ms << "ms)";
    bus_.publish({"log", ss.str()});
}

void TaskManager::runOnce() {
    auto now = std::chrono::steady_clock::now();

    for (auto& t : tasks_) {
        auto elapsed = std::chrono::duration_cast<std::chrono::milliseconds>(
                           now - t.next_run)
                           .count();

        if (elapsed >= t.period_ms) {
            t.callback();
            t.next_run = now;
        }
    }
}
