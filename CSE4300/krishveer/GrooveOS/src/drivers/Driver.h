#pragma once
#include <string>

class Driver {
public:
    Driver(std::string name) : name_(std::move(name)) {}
    virtual ~Driver() = default;

    const std::string& name() const { return name_; }

    // Optional: driver-specific initialization
    virtual void init() {}

private:
    std::string name_;
};
