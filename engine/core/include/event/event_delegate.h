#pragma once
#include <iostream>
namespace ecs::event {
    class EventBase;

    namespace internal {
        using EventDelegateId = size_t;

        class EventBaseDelegate {
        public:
            virtual ~EventBaseDelegate() {}
            virtual inline void invoke(const EventBase* const event) = 0;

            virtual inline EventDelegateId getDelegateId() const = 0;

            virtual inline size_t getStaticEventTypeId() const = 0;

            virtual bool operator==(const EventBaseDelegate* other) const = 0;

            virtual EventBaseDelegate* clone() = 0;
        };

        template<class Class, class EventType>
        class EventDelegate : public EventBaseDelegate {
            typedef void(Class::*Callback)(const EventType* const);

            Class* m_Receiver;
            Callback m_Callback;

        public:
            EventDelegate(Class* receiver, Callback& callbackFunction) : m_Receiver(receiver), m_Callback(callbackFunction) {}

            virtual EventBaseDelegate* clone() override {
                return new EventDelegate(m_Receiver, m_Callback);
            }

            virtual inline void invoke(const EventBase* const event) override {
                (m_Receiver->*m_Callback)(reinterpret_cast<const EventType* const>(event));
            }

            virtual inline EventDelegateId getDelegateId() const override {
                static const EventDelegateId DELEGATE_ID { typeid(Class).hash_code() ^ typeid(Callback).hash_code() };
                return DELEGATE_ID;
            }


            virtual inline size_t getStaticEventTypeId() const override {
                static const size_t SEID { EventType::STATIC_EVENT_TYPE_ID };
                return SEID;
            }

            virtual bool operator==(const EventBaseDelegate* other) const override {
                if (!other) {
                    return false;
                }

                if (getDelegateId() != other->getDelegateId()) {
                    return false;
                }
                EventDelegate* delegate = (EventDelegate*)other;

                return ((this->m_Callback == delegate->m_Callback) && (this->m_Receiver == delegate->m_Receiver));
            }

        };
    }
}
