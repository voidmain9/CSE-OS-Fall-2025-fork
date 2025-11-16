#include "apps/Shell.h"
#include <sstream>

// stores references to Kernel and MessageBus
Shell::Shell(Kernel& kernel, MessageBus& bus)
    : kernel_(kernel), bus_(bus) { }

// Splits an input line into whitespace-separated tokens
std::vector<std::string> Shell::tokenize(const std::string& line) {
    std::stringstream ss(line);
    std::string temp;
    std::vector<std::string> tokens;

    while (ss >> temp) {
        tokens.push_back(temp);
    }
    return tokens;
}

// Executes comand based on parsed tokens
void Shell::handleCommand(const std::vector<std::string>& tokens) {
    if (tokens.empty()) return;

    const std::string& cmd = tokens[0];

    // "help" command
    if (cmd == "help") {
        std::cout << "Commands: help, ps, drivers, send <topic> <msg>, log, shutdown\n";
    }

    // "ps" - list tasks
    else if (cmd == "ps") {
        auto& tm = kernel_.taskManager();
        std::cout << "Tasks:\n";
        for (auto& t : tm.tasks()) {
            std::cout << " - " << t.id << ": " << t.name << "\n";
        }
    }

    // "drivers" - list loaded drivers
    else if (cmd == "drivers") {
        auto& dm = kernel_.driverManager();
        std::cout << "Drivers Loaded:\n";

        int i = 0;
        for (auto& d : dm.drivers()) {
            std::cout << " - " << i++ << ": " << d->name() << "\n";
        }
    }

    // "send" - publish a message to MessageBus
    else if (cmd == "send" && tokens.size() >= 3) {
        std::string topic = tokens[1];
        std::string payload;

        // Combine remaining tokens into the message payload
        for (size_t i = 2; i < tokens.size(); i++) {
            payload += tokens[i] + " ";
        }

        bus_.publish({topic, payload});
        std::cout << "Message sent.\n";
    }

    // "log" - print SysLog contents
    else if (cmd == "log") {
        std::cout << "=== System Log ===\n";
        kernel_.syslog().printAll();
        std::cout << "==================\n";
    }

    // "shutdown" - request kernel shutdown
    else if (cmd == "shutdown") {
        kernel_.shutdown();
    }

    // Unknown command fallback
    else {
        std::cout << "Unknown command: " << cmd << "\n";
    }
}

// Called each scheduler tick; reads user input and processes a command
void Shell::tick() {
    std::cout << "> " << std::flush;

    std::string line;
    if (std::getline(std::cin, line)) {
        auto tokens = tokenize(line);
        handleCommand(tokens);
    }
}
