#include "kernel/Kernel.h"
#include <thread>
#include <chrono>

Kernel::Kernel()
    : running_(false),
      messageBus_(),
      taskManager_(messageBus_), // inject MessageBus into TaskManager
      driverManager_(),
      syslog_() {}

Kernel& Kernel::instance() {
    static Kernel k;
    return k;
}

void Kernel::boot() {
    std::cout << "=== GrooveOS Booting ===\n";
    syslog_.add("Kernel booting...");

    // SysLog subscribes to all "log" messages on the MessageBus
    messageBus_.subscribe("log", [this](const Message& msg) {
        syslog_.add(msg.payload);
    });

    // Initialize drivers
    driverManager_.initAll();
    syslog_.add("Drivers initialized.");

    running_ = true;
}

void Kernel::run() {
    std::cout << "=== GrooveOS Running ===\n";

    while (running_) {
        taskManager_.runOnce();
        std::this_thread::sleep_for(std::chrono::milliseconds(1));
    }

    std::cout << "=== GrooveOS Stopped ===\n";
}

void Kernel::shutdown() {
    std::cout << "[Kernel] Shutdown requested\n";
    syslog_.add("Kernel shutting down.");
    running_ = false;
}
