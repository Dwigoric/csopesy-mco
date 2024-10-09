#ifndef ASCHEDULER_H
#define ASCHEDULER_H


#include <vector>

#include "Process.h"


class AScheduler {
public:
    virtual ~AScheduler() = default;

    enum SchedulingAlgorithm {
        FCFS,
        ROUND_ROBIN,
        SHORTEST_JOB_FIRST_PREEMPTIVE,
        SHORTEST_JOB_FIRST_NON_PREEMPTIVE,
    };

    explicit AScheduler(SchedulingAlgorithm algorithm);

    void run();

    void stop();

    virtual void init() = 0;

    virtual void execute() = 0;

protected:
    std::vector<Process> processes;
    std::vector<Process> readyQueue;

private:
    SchedulingAlgorithm algorithm;

    bool running = false;
};


#endif //ASCHEDULER_H