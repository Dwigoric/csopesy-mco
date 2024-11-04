#ifndef ASCHEDULER_H
#define ASCHEDULER_H


#include <vector>
#include <mutex>

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

    void scheduleProcess(const std::shared_ptr<Process> &process);

    void startSpawning();

    void stopSpawning();

    void run();

    void stop();

    virtual void init() = 0;

    void onTick() const;

    virtual void execute() = 0;

protected:
    std::vector<std::shared_ptr<Process> > readyQueue;

    std::mutex queueMutex;

    bool isSpawning = false;

private:
    SchedulingAlgorithm algorithm;

    bool running = false;
};


#endif //ASCHEDULER_H
