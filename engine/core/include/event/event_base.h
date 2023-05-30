#pragma once
#include "timer.h"
#include <iostream>

namespace ecs::event {
    using EventTypeId = size_t;
    using EventTimestamp = utils::TimeStamp;

    class EventBase {
    public:
        EventBase(EventTypeId typeId) : m_TimeCreated(utils::Timer().GetTimeStamp()), m_TypeId(typeId) {}
        inline const EventTypeId	getEventTypeID()	const { return m_TypeId; }
        inline const EventTimestamp getTimeCreated()	const { return m_TimeCreated; }
        void setEventTypeId(EventTypeId id) {m_TypeId = id;}
    private:
        EventTypeId	m_TypeId;
        EventTimestamp m_TimeCreated;
    };
}
