#pragma once
#include "event_base.h"
#include "event_dispatcher.h"
#include <vector>
#include <unordered_map>
#include <memory>

namespace ecs::event {

    class EventHandler {
        using EventDispatcherMap = std::unordered_map<EventTypeId, internal::EventBaseDispatcher*>;
        using EventStorage = std::vector<std::shared_ptr<EventBase>>;
    public:
        EventHandler() {}
        ~EventHandler() {}

        inline void ClearEventBuffer() {
            m_EventStorage.clear();
        }

        inline void ClearEventDispatcher() {
            m_EventDispatcherMap.clear();
        }

        template<class E, class... ARGS>
        void Send(ARGS&&... eventArgs) {
            std::shared_ptr<EventBase> event = std::make_shared<E>(std::forward<ARGS>(eventArgs)...);
            event->setEventTypeId(E::STATIC_EVENT_TYPE_ID);
            m_EventStorage.push_back(event);
        }

        void DispatchEvents() {
            for (auto& event : m_EventStorage) {
                if (event) {
                    auto iter = m_EventDispatcherMap.find(event->getEventTypeID());
                    if (iter != m_EventDispatcherMap.end()) {
                        iter->second->dispatch(event.get());
                    }
                    event = nullptr;
                }
            }
            //ClearEventBuffer();
        }

        template<class E>
        inline void AddEventCallback(internal::EventBaseDelegate* const eventDelegate) {
            EventTypeId eventTypeId = E::STATIC_EVENT_TYPE_ID;

            auto iter = m_EventDispatcherMap.find(eventTypeId);
            if (iter == m_EventDispatcherMap.end()) {
                std::pair<EventTypeId, internal::EventBaseDispatcher*> eventTypeIdToDispatcher(eventTypeId, new internal::EventDispatcher<E>());

                eventTypeIdToDispatcher.second->addEventCallback(eventDelegate);

                m_EventDispatcherMap.insert(eventTypeIdToDispatcher);
                return;
            }
            m_EventDispatcherMap[eventTypeId]->addEventCallback(eventDelegate);
        }

        inline void RemoveEventCallback(internal::EventBaseDelegate* eventDelegate) {
            auto typeId = eventDelegate->getStaticEventTypeId();
            auto iter = m_EventDispatcherMap.find(typeId);
            if (iter != m_EventDispatcherMap.end()) {
                m_EventDispatcherMap[typeId]->removeEventCallback(eventDelegate);
            }
        }
    private:
        EventHandler(const EventHandler&);
        EventHandler& operator=(EventHandler&);

        EventDispatcherMap m_EventDispatcherMap;
        EventStorage m_EventStorage;
    };
}
