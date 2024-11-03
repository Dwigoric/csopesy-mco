#ifndef SCHEDULERTHREAD_H
#define SCHEDULERTHREAD_H


#include "Thread.h"
#include "CustomThread.h"
#include "../process/FCFSScheduler.h"
#include "../process/RoundRobinScheduler.h"

class SchedulerThread final : public Thread {
public:
    static SchedulerThread *getInstance();

    SchedulerThread &operator=(SchedulerThread const &) = delete;

    static void destroy();

    static void initialize(const std::string& scheduler, int quantum);

    bool createProcess(const std::string &name);

    void registerProcess(const std::shared_ptr<Process> &process);

    std::vector<std::shared_ptr<Process> > getProcessList();

    void startSpawning();

    void stopSpawning();

    void stopScheduler() const;

    void switchScheduler(const std::string &scheduler);

    void run() override;

private:
    SchedulerThread(const std::string &scheduler, int quantum);

    ~SchedulerThread();

    SchedulerThread(SchedulerThread const &) {
    };

    static SchedulerThread *instance;

    bool isSpawning = false;
    int processCounter = 0;
    std::vector<std::shared_ptr<Process> > processes;
    CustomThread *spawnerThread = nullptr;

    FCFSScheduler *schedulerFCFS = nullptr;
    RoundRobinScheduler *schedulerRR = nullptr;
    // Add other schedulers here

    AScheduler *currentScheduler = nullptr;
};


#endif //SCHEDULERTHREAD_H
