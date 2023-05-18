#pragma once
#include "event_base.h"
#include "event_dispatcher.h"
#include <vector>
#include <unordered_map>

namespace ecs::event {

    class  EventHandler {
        using EventDispatcherMap = std::unordered_map<EventTypeId, internal::EventBaseDispatcher*>;
        using EventStorage = std::vector<EventBase*>;
    public:
        EventHandler();
        ~EventHandler();

        inline void ClearEventBuffer() {
            m_EventStorage.clear();
        }

        inline void ClearEventDispatcher() {
            m_EventDispatcherMap.clear();
        }

        template<class E, class... ARGS>
        void Send(ARGS&&... eventArgs) {}

        void DispatchEvents() {}

    private:
        EventHandler(const EventHandler&);
        EventHandler& operator=(EventHandler&);

        EventDispatcherMap	m_EventDispatcherMap;
        EventStorage m_EventStorage;

        template<class E>
        inline void AddEventCallback(internal::EventBaseDelegate* const eventDelegate) { }

        inline void RemoveEventCallback(internal::EventBaseDelegate* eventDelegate) { }
    };
}