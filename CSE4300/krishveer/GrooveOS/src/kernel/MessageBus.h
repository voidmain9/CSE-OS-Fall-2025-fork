#pragma once
#include <functional>
#include <string>
#include <vector>

struct Message {
    std::string topic;
    std::string payload;
};

class MessageBus {
public:
    using Callback = std::function<void(const Message&)>;

    void subscribe(const std::string& topic, Callback cb);
    void publish(const Message& msg);

private:
    struct Sub { std::string topic; Callback cb; };
    std::vector<Sub> subs_;
};
