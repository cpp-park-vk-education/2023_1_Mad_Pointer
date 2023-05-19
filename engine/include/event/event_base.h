#pragma once
#include "../../utils/timer.h"
#include <iostream>

namespace ecs::event {
    using EventTypeId = size_t;
    using EventTimestamp = utils::TimeStamp;

    class EventBase {
    public:
        EventBase(EventTypeId typeId) : m_TimeCreated(utils::Timer().GetTimeStamp()), m_TypeId(typeId) {}
        inline const EventTypeId	getEventTypeID()	const { return this->m_TypeId; }
        inline const EventTimestamp getTimeCreated()	const { return this->m_TimeCreated; }
    private:
        EventTypeId		m_TypeId;
        EventTimestamp	m_TimeCreated;
    };
}