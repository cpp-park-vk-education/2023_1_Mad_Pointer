#pragma once
#include <chrono>



namespace ecs::utils {
    union TimeStamp {
        float m_asFloat;
        uint32_t m_asUint;

        TimeStamp(): m_asUint(0u) { }

        TimeStamp(float floatValue) : m_asFloat(floatValue) {}
        operator uint32_t() const {return m_asUint; }

        inline const bool operator==(const TimeStamp& other) const {return m_asUint == other.m_asUint; }
        inline const bool operator!=(const TimeStamp& other) const {return m_asUint != other.m_asUint; }

        inline const bool operator<(const TimeStamp& other) const {return m_asFloat < other.m_asFloat; }
        inline const bool operator>(const TimeStamp& other) const {return m_asFloat > other.m_asFloat; }
    };

    using Elapsed = std::chrono::duration<float, std::milli>;
    class Timer {
    public:
        Timer();
        ~Timer();

        void Tick(float ms);
        void Reset();

        inline TimeStamp GetTimeStamp() const {
            return TimeStamp(this->m_Elapsed.count());
        }

    private:
        Elapsed m_Elapsed;
    };

} // namespace ecs::utils