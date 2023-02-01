#ifndef RAII_TIME_AND_LOG_HPP
#define RAII_TIME_AND_LOG_HPP

// Headers from this project
#include <iostream>
#include <chrono>

namespace timer {

class raii_time_and_log
{
public:
        raii_time_and_log()
        {
                m_start = std::chrono::high_resolution_clock::now();
        }

        ~raii_time_and_log()
        {
                m_end = std::chrono::high_resolution_clock::now();
                m_duration = m_end - m_start;
                float ms = m_duration.count() * 1000.0f;
                std::cout << ms << " ms " << std::endl;
        }
private:
        std::chrono::time_point<std::chrono::high_resolution_clock> m_start;
        std::chrono::time_point<std::chrono::high_resolution_clock> m_end;
        std::chrono::duration<float> m_duration;
}; // raii_timer 

} // timer

#endif // RAII_TIME_AND_LOG_HPP 


