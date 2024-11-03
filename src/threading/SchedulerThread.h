#ifndef SCHEDULERTHREAD_H
#define SCHEDULERTHREAD_H


#include "Thread.h"
#include "CustomThread.h"
#include "../process/FCFSScheduler.h"

class SchedulerThread final : public Thread {
public:
    static SchedulerThread *getInstance();

    SchedulerThread &operator=(SchedulerThread const &) = delete;

    static void destroy();

    static void initialize();

    bool createProcess(const std::string &name);

    void registerProcess(const std::shared_ptr<Process> &process);

    std::vector<std::shared_ptr<Process> > getProcessList();

    void startSpawning();

    void stopSpawning();

    void stopScheduler() const;

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
    std::vector<std::shared_ptr<Process> > processes;
    CustomThread *spawnerThread = nullptr;

    FCFSScheduler *schedulerFCFS = nullptr;
    // Add other schedulers here

    AScheduler *currentScheduler = nullptr;
};


#endif //SCHEDULERTHREAD_H
