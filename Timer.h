#ifndef DISCMEASUREMENT_TIMER_H
#define DISCMEASUREMENT_TIMER_H


#include <chrono>

class Timer {
private:
    std::chrono::system_clock::time_point start_point, stop_point;
    double time;

    double count_time() {
        std::chrono::system_clock::time_point epoch;
        if (start_point == epoch || stop_point == epoch) throw ReadException();
        return std::chrono::duration<double>(stop_point - start_point).count();
    }

public:
    class ReadException : std::exception { };

    void start() {
        start_point = std::chrono::system_clock::now();
    }
    void stop() {
        stop_point = std::chrono::system_clock::now();
        time = count_time();
    }
    double read() {
        return time;
    }
};

#endif //DISCMEASUREMENT_TIMER_H
