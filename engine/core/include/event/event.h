#pragma once
#include "event_base.h"
#include "family_type_id.h"

namespace ecs::event {
    template<typename EventType>
    class Event : public EventBase {
    public:
        static const EventTypeId STATIC_EVENT_TYPE_ID;

        Event() : EventBase(STATIC_EVENT_TYPE_ID) {}
    };


}

template<class EventType>
const ecs::event::EventTypeId ecs::event::Event<EventType>::STATIC_EVENT_TYPE_ID = ecs::utils::internal::FamilyTypeId<EventBase>::get<EventType>();