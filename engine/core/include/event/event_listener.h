#pragma once
#include "engine.h"
#include "event_delegate.h"

#include <list>
namespace ecs::event {
    class EventListenerBase {
        using RegisteredCallbacks = std::list<internal::EventBaseDelegate*>;
    public:

        EventListenerBase(ecs::Engine* engine) : m_engine(engine) {}
        virtual ~EventListenerBase() = default;

        template<class Event, class Callback>
        inline void registerEventCallback(void(Callback::*callback)(const Event* const)) {
            internal::EventBaseDelegate* eventDelegate = new internal::EventDelegate<Callback, Event>(static_cast<Callback*>(this), callback);

            m_RegisteredCallbacks.push_back(eventDelegate);
            m_engine->subscribeEvent<Event>(eventDelegate);
        }

        template<class Event, class Callback>
        inline void unregisterEventCallback(void(Callback::*callback)(const Event* const)) {
            internal::EventDelegate<Callback, Event> delegate(static_cast<Callback*>(this), callback);

            for (auto cb : this->m_RegisteredCallbacks) {
                if (cb->getDelegateId() == delegate.getDelegateId()) {
                    m_RegisteredCallbacks.remove_if(
                            [&](const internal::EventBaseDelegate* other) {
                                return other == cb;
                            }
                    );

                    m_engine->unsubscribeEvent(&delegate);
                    break;
                }
            }
        }

        void unregisterAllEventCallbacks() {}


        ecs::Engine* getEngine() const {
            return m_engine;
        }
    private:
        ecs::Engine* m_engine;
        RegisteredCallbacks m_RegisteredCallbacks;
    };
}
