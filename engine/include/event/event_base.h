#include <iostream>

namespace ecs::event {
    using EventTypeId = size_t;
    struct EventTimestamp {

    };

    class EventBase {
    public:
        EventBase(EventTypeId typeId);
        inline const EventTypeId	getEventTypeID()	const { return this->m_TypeId; }
        inline const EventTimestamp getTimeCreated()	const { return this->m_TimeCreated; }
    private:
        EventTypeId		m_TypeId;
        EventTimestamp	m_TimeCreated;
    };
}