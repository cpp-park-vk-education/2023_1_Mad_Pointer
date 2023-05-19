#pragma once
#include "api.h"
#include "event_delegate.h"

#include <list>
namespace ecs::event {
    class EventListenerBase {
        using RegisteredCallbacks = std::list<internal::EventBaseDelegate*>;

    public:

        EventListenerBase() {}
        virtual ~EventListenerBase() {}

        template<class Event, class Callback>
        inline void registerEventCallback(void(Callback::*callback)(const Event* const)) {
            internal::EventBaseDelegate* eventDelegate = new internal::EventDelegate<Callback, Event>(static_cast<Callback*>(this), callback);

            m_RegisteredCallbacks.push_back(eventDelegate);
            ECS_Engine->SubscribeEvent<Event>(eventDelegate);
        }

        template<class Event, class Callback>
        inline void unregisterEventCallback(void(Callback::*callback)(const Event* const)) {
            internal::EventDelegate<Callback, Event> delegate(static_cast<Callback*>(this), callback);

            for (auto cb : this->m_RegisteredCallbacks) {
                if (cb->getDelegateId() == delegate.GetDelegateId()) {
                    m_RegisteredCallbacks.remove_if(
                            [&](const internal::EventBaseDelegate* other)
                            {
                                return other->operator==(cb);
                            }
                    );

                    ECS_Engine->UnsubscribeEvent(&delegate);
                    break;
                }
            }
        }

        void unregisterAllEventCallbacks();
    private:
        RegisteredCallbacks m_RegisteredCallbacks;
    };
}

