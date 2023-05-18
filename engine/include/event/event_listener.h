#pragma once
#include "event_delegate.h"
#include <list>
namespace ecs::event {
    class EventListenerBase {
        using RegisteredCallbacks = std::list<internal::EventBaseDelegate*>;

    public:

        EventListenerBase() {}
        virtual ~EventListenerBase() {}

        template<class Event, class Callback>
        inline void registerEventCallback(void(Callback::*callback)(const Event* const)) {}

        template<class Event, class Callback>
        inline void unregisterEventCallback(void(Callback::*callback)(const Event* const)) {}

        void unregisterAllEventCallbacks() {}
    private:
        RegisteredCallbacks m_RegisteredCallbacks;
    };
}

