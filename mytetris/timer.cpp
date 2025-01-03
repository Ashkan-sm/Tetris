#include "timer.h"

Timer::Timer()
{
    start_time = std::chrono::high_resolution_clock::now();
}
