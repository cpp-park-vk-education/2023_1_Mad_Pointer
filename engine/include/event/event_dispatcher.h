#pragma once
#include "event_base_dispatcher.h"
#include <list>
namespace ecs::event::internal {

    template<class T>
    class EventDispatcher : public EventBaseDispatcher {
        using EventDelegateList	= std::list<EventBaseDelegate*>;
        using PendingRemoveDelegates = std::list<EventBaseDelegate*>;

    public:
        EventDispatcher() : m_Locked(false) {}

        virtual ~EventDispatcher() {
            this->m_PendingRemoveDelegates.clear();
            this->m_EventCallbacks.clear();
        }

        inline void dispatch(EventBase* event) override {
            m_Locked = true;
            for (const auto delegate : m_PendingRemoveDelegates) {
                auto result = std::find_if(m_EventCallbacks.begin(), m_EventCallbacks.end(), [delegate](const EventBaseDelegate* other){return *delegate == other;});
                if (result != m_EventCallbacks.end()) {
                    EventBaseDelegate* ptrMem = (EventBaseDelegate*)(*result);
                    m_EventCallbacks.erase(result);

                    delete ptrMem;
                    ptrMem = nullptr;
                }
                m_PendingRemoveDelegates.clear();
            }

            for (const auto eventCallback : m_EventCallbacks) {
                eventCallback->invoke(event);
            }
            m_Locked = false;
        }

        virtual void addEventCallback(EventBaseDelegate* const eventDelegate) override {
            auto result = std::find_if(m_PendingRemoveDelegates.begin(), m_PendingRemoveDelegates.end(),
                                       [&](const EventBaseDelegate* other) {
                                           return *eventDelegate == other;
                                       });

            if (result != m_PendingRemoveDelegates.end()) {
                m_PendingRemoveDelegates.erase(result);
                return;
            }

            m_EventCallbacks.push_back(eventDelegate);
        }

        virtual void removeEventCallback(EventBaseDelegate* eventDelegate) override {
            if (!m_Locked) {
                auto result = std::find_if(m_EventCallbacks.begin(), m_EventCallbacks.end(),
                                           [&](const EventBaseDelegate* other) {
                                               return *other == eventDelegate;
                                           });

                if (result != m_EventCallbacks.end()) {
                    EventBaseDelegate* ptrMem = (EventBaseDelegate*)(*result);

                    m_EventCallbacks.erase(result);

                    delete ptrMem;
                    ptrMem = nullptr;
                }
            }
            else {
                auto result = std::find_if(m_EventCallbacks.begin(), m_EventCallbacks.end(),
                                           [&](const EventBaseDelegate *other) {
                                               return other == eventDelegate;
                                           });

                assert(result != m_EventCallbacks.end() && "");
                m_PendingRemoveDelegates.push_back((*result));
            }
        }

        virtual inline size_t getEventCallbackCount() const override { return this->m_EventCallbacks.size(); }

    private:
        PendingRemoveDelegates m_PendingRemoveDelegates;
        EventDelegateList m_EventCallbacks;
        bool m_Locked;
    };
}

