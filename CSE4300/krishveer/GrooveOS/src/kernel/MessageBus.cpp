#include "kernel/MessageBus.h"

void MessageBus::subscribe(const std::string& topic, Callback cb) {
    subs_.push_back({topic, std::move(cb)});
}

void MessageBus::publish(const Message& msg) {
    // Deliver to subscribers
    for (auto& s : subs_) {
        if (s.topic == msg.topic) {
            s.cb(msg);
        }
    }
}

