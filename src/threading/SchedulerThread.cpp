#include "SchedulerThread.h"

#include <thread>

SchedulerThread *SchedulerThread::instance = nullptr;

SchedulerThread::SchedulerThread() {
    this->schedulerFCFS = new FCFSScheduler();

    this->currentScheduler = this->schedulerFCFS;
}

void SchedulerThread::startSpawning() {
    //while (this->isSpawning) {
    //    std::shared_ptr<Process> process = std::make_shared<Process>(this->processCounter++,
    //                                                                 std::format("process_{}", this->processCounter));;

    //    this->currentScheduler->scheduleProcess(*process);

    //    // Add delay of 0.5s
    //    sleep(500);
    //}

    for (int i = 0; i < 10; i++) {
        std::shared_ptr<Process> process = std::make_shared<Process>(this->processCounter++,
            std::format("screen_{}", this->processCounter));

        for (int j = 0; j < 100; j++) {
            process->addCommand(AInstruction::PRINT);
        }

        this->currentScheduler->scheduleProcess(*process);
    }
}

void SchedulerThread::stopSpawning() {
    this->isSpawning = false;
}

void SchedulerThread::stopScheduler() const {
    this->currentScheduler->stop();
}

void SchedulerThread::switchScheduler(const std::string &scheduler) {
    this->currentScheduler->stop();

    if (scheduler == "FCFS") {
        this->currentScheduler = this->schedulerFCFS;
    }
    // Add more schedulers here
    else {
        throw std::runtime_error("Invalid scheduler");
    }

    this->currentScheduler->run();
}

void SchedulerThread::run() {
    if (this->currentScheduler == nullptr) {
        throw std::runtime_error("Invalid scheduler");
    }

    this->startSpawning();
    this->currentScheduler->run();
}

void SchedulerThread::registerProcess(const Process &process) {
    this->processes.push_back(process);
}

std::vector<Process> SchedulerThread::getProcessList() {
    return this->processes;
}

SchedulerThread *SchedulerThread::getInstance() {
    return instance;
}

void SchedulerThread::destroy() {
    delete getInstance();
}

void SchedulerThread::initialize() {
    if (instance == nullptr) {
        instance = new SchedulerThread();
    }
}
