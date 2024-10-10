#ifndef SCHEDULERTHREAD_H
#define SCHEDULERTHREAD_H


#include "Thread.h"
#include "../process/FCFSScheduler.h"

class SchedulerThread final : public Thread {
public:
    static SchedulerThread *getInstance();

    SchedulerThread(SchedulerThread const &) = delete;

    SchedulerThread &operator=(SchedulerThread const &) = delete;

    static void destroy();

    void switchScheduler(const std::string &scheduler);

    void run() override;

private:
    SchedulerThread();

    ~SchedulerThread() override = default;

    static SchedulerThread *instance;

    FCFSScheduler *schedulerFCFS = nullptr;
    // Add other schedulers here

    AScheduler *currentScheduler = nullptr;
};


#endif //SCHEDULERTHREAD_H
