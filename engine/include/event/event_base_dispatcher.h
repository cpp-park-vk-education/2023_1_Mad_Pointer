#include "event_delegate.h"
namespace ecs::event::internal {
    class EventBaseDispatcher {
    public:

        virtual ~EventBaseDispatcher() {}

        virtual void dispatch(EventBase* event) = 0;

        virtual void addEventCallback(EventBaseDelegate* const eventDelegate) = 0;
        virtual void removeEventCallback(EventBaseDelegate* eventDelegate) = 0;

        virtual inline size_t getEventCallbackCount() const = 0;
    };
}

