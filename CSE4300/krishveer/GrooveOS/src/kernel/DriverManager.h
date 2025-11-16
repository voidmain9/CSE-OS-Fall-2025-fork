#pragma once
#include <vector>
#include <memory>
#include <iostream>

#include "drivers/Driver.h"

class DriverManager {
public:
    void registerDriver(std::unique_ptr<Driver> driver);

    const std::vector<std::unique_ptr<Driver>>& drivers() const {
        return drivers_;
    }

    void initAll();

private:
    std::vector<std::unique_ptr<Driver>> drivers_;
};
