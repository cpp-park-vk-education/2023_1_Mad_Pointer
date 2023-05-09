#include "event_base.h"

namespace ecs::event {
    template<typename EventType>
    class Event : public EventBase {
    public:
        static const EventTypeId STATIC_EVENT_TYPE_ID;

        Event() : EventBase(STATIC_EVENT_TYPE_ID) {}
    };

    template<class EventType>
    const EventTypeId Event<EventType>::STATIC_EVENT_TYPE_ID { typeid(EventType).hash_code() };
}