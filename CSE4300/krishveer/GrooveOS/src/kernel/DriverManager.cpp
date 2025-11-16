#include "kernel/DriverManager.h"

void DriverManager::registerDriver(std::unique_ptr<Driver> driver) {
    std::cout << "[DriverManager] Registered driver: "
              << driver->name() << "\n";

    drivers_.push_back(std::move(driver));
}

void DriverManager::initAll() {
    for (auto& d : drivers_) {
        d->init();
    }
}
