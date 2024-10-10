#include "SchedulerThread.h"

SchedulerThread::SchedulerThread() {
    this->schedulerFCFS = new FCFSScheduler();

    this->currentScheduler = this->schedulerFCFS;
}

void SchedulerThread::switchScheduler(const std::string &scheduler) {
    if (scheduler == "FCFS") {
        this->currentScheduler = this->schedulerFCFS;
    }
}

void SchedulerThread::run() {
    if (this->currentScheduler == nullptr) {
        throw std::runtime_error("Invalid scheduler");
    }

    this->currentScheduler->execute();
}

SchedulerThread *SchedulerThread::getInstance() {
    return instance;
}

void SchedulerThread::destroy() {
    delete getInstance();
}
