#include "timer.h"

namespace ecs::utils {
    Timer::Timer() : m_Elapsed(0) {}

    Timer::~Timer() {}

    void Timer::Tick(float ms) {
        m_Elapsed += std::chrono::duration<float, std::ratio<1, 1000>>(ms);
    }

    void Timer::Reset() {
        m_Elapsed = Elapsed::zero();
    }
}
