#ifndef SCHEDULERTHREAD_H
#define SCHEDULERTHREAD_H


#include "Thread.h"
#include "../process/FCFSScheduler.h"

class SchedulerThread final : public Thread {
public:
    static SchedulerThread *getInstance();

    SchedulerThread &operator=(SchedulerThread const &) = delete;

    static void destroy();

    static void initialize();

    void startSpawning();

    void stopSpawning();

    void switchScheduler(const std::string &scheduler);

    void run() override;

private:
    SchedulerThread();

    ~SchedulerThread() override = default;

    SchedulerThread(SchedulerThread const &) {
    };

    static SchedulerThread *instance;

    bool isSpawning = false;

    int processCounter = 0;

    FCFSScheduler *schedulerFCFS = nullptr;
    // Add other schedulers here

    AScheduler *currentScheduler = nullptr;
};


#endif //SCHEDULERTHREAD_H