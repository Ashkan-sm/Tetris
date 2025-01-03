#ifndef TIMER_H
#define TIMER_H
#include <chrono>

class Timer {
public:
    // Constructor: starts the timer
    Timer();

    // Reset the timer
    void reset() {
        start_time = std::chrono::high_resolution_clock::now();
    }

    // Get the elapsed time in seconds
    double elapsed_seconds() const {
        auto end_time = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double> duration = end_time - start_time;
        return duration.count();
    }

    // Get the elapsed time in milliseconds
    double elapsed_milliseconds() const {
        auto end_time = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double, std::milli> duration = end_time - start_time;
        return duration.count();
    }

    // Get the elapsed time in microseconds
    double elapsed_microseconds() const {
        auto end_time = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double, std::micro> duration = end_time - start_time;
        return duration.count();
    }

private:
    std::chrono::time_point<std::chrono::high_resolution_clock> start_time;
};

#endif // TIMER_H
