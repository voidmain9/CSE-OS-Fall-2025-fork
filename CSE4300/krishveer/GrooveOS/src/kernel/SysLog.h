#pragma once
#include <vector>
#include <string>
#include <iostream>

class SysLog {
public:
    void add(const std::string& entry) {
        logs_.push_back(entry);
    }

    const std::vector<std::string>& logs() const {
        return logs_;
    }

    void printAll() const {
        for (const auto& entry : logs_) {
            std::cout << entry << "\n";
        }
    }

private:
    std::vector<std::string> logs_;
};
