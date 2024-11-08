#ifndef ASCHEDULER_H
#define ASCHEDULER_H


#include <vector>
#include <mutex>

#include "Process.h"
#include "../cpu/CPUWorker.h"
#include "../memory/IMemoryAllocator.h"


class AScheduler {
public:
    virtual ~AScheduler() = default;

    enum SchedulingAlgorithm {
        FCFS,
        ROUND_ROBIN,
        SHORTEST_JOB_FIRST_PREEMPTIVE,
        SHORTEST_JOB_FIRST_NON_PREEMPTIVE,
    };

    explicit AScheduler(SchedulingAlgorithm algorithm, std::shared_ptr<IMemoryAllocator> memoryAllocator);

    void scheduleProcess(const std::shared_ptr<Process> &process);

    bool assignQueuedProcess(CPUWorker* core, int coreId);

    void startSpawning();

    void stopSpawning();

    void run();

    void stop();

    virtual void init() = 0;

    void onTick();

    virtual void execute() = 0;

protected:
    std::vector<std::shared_ptr<Process> > readyQueue;

    std::mutex queueMutex;

    bool isSpawning = false;

    std::shared_ptr<IMemoryAllocator> memoryAllocator;

    int ticks = 0;

private:
    SchedulingAlgorithm algorithm;

    bool running = false;

    int spawnFrequency;
    int spawnCounter = 0;
};


#endif //ASCHEDULER_H
