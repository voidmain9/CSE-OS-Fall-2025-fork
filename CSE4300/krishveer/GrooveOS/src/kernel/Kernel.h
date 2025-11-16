#pragma once

#include <atomic>
#include <iostream>

#include "TaskManager.h"
#include "MessageBus.h"
#include "DriverManager.h"
#include "SysLog.h"

class Kernel {
public:
    static Kernel& instance();

    void boot();
    void run();
    void shutdown();

    TaskManager& taskManager()   { return taskManager_; }
    MessageBus&  messageBus()    { return messageBus_; }
    DriverManager& driverManager(){ return driverManager_; }
    SysLog& syslog()             { return syslog_; }

private:
    Kernel(); // custom ctor so we can wire subsystems

    std::atomic<bool> running_;

    // Order matters: MessageBus must be constructed before TaskManager
    MessageBus   messageBus_;
    TaskManager  taskManager_;
    DriverManager driverManager_;
    SysLog       syslog_;
};
