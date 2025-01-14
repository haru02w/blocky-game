#pragma once
#include <functional>
#include <string>
#include <type_traits>
#include <unordered_map>
#include <vector>
#include "EventBase.hpp"

// define custom typename with checking
template <typename T>
concept EventTypename = std::is_base_of_v<EventBase, T>;

// The event handler
class EventManager {
public:
    template <EventTypename T> using EventCallback = std::function<void(T &&)>;

    EventManager() = default;
    ~EventManager() = default;

    // Add events to be executed every time they happens
    template <EventTypename T>
    EventManager &subscribe(const std::string &name, EventCallback<T> callback)
    {
        subscribers[name].emplace_back([callback](EventBase &&e) {
            // use this lambda to cast to derived class first
            callback(static_cast<T &&>(std::move(e)));
        });
        return *this;
    }

    // Remove events from the execution queue
    template <EventTypename T>
    EventManager &unsubscribe(const std::string &name)
    {
        subscribers.erase(name);
        return *this;
    }

    // Run events of "name" with "event" data
    template <EventTypename T>
    EventManager &dispatch(const std::string &name, T &&event)
    {
        std::vector<EventCallback<EventBase>> &subsOnEvent = subscribers[name];
        for (const EventCallback<EventBase> &callback : subsOnEvent)
            callback(std::move(event));
        return *this;
    }

private:
    std::unordered_map<std::string, std::vector<EventCallback<EventBase>>>
        subscribers;
};
