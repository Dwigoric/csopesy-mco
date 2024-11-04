#ifndef SCHEDULERTHREAD_H
#define SCHEDULERTHREAD_H


#include "Thread.h"
#include "../process/AScheduler.h"

class SchedulerThread final : public Thread {
public:
    static SchedulerThread *getInstance();

    SchedulerThread &operator=(SchedulerThread const &) = delete;

    static void destroy();

    static void initialize(const std::string &scheduler, int quantum);

    bool createProcess(const std::string &name);

    std::vector<std::shared_ptr<Process> > getProcessList();

    [[nodiscard]] int getProcessCounter() const;

    void startSpawning() const;

    void stopSpawning() const;

    void stopScheduler() const;

    void run() override;

private:
    SchedulerThread(const std::string &scheduler, int quantum);

    // ~SchedulerThread();

    SchedulerThread(SchedulerThread const &) {
    };

    static SchedulerThread *instance;

    Thread *globalTicker = nullptr;

    int processCounter = 0;
    std::vector<std::shared_ptr<Process> > processes;

    AScheduler *currentScheduler = nullptr;

    void registerProcess(const std::shared_ptr<Process> &process);
};


#endif //SCHEDULERTHREAD_H
