#include "AScheduler.h"

#include "../threading/SchedulerThread.h"

AScheduler::AScheduler(const SchedulingAlgorithm algorithm) {
    this->algorithm = algorithm;
}

void AScheduler::scheduleProcess(const std::shared_ptr<Process> &process) {
    this->readyQueue.push_back(process);
    process->setState(Process::READY);
}

void AScheduler::run() {
    this->running = true;
    init();
    while (this->running) {
        execute();
    }
}

void AScheduler::onTick() const {
    if (this->isSpawning) {
        SchedulerThread::getInstance()->createProcess(
            std::format("screen_{}", SchedulerThread::getInstance()->getProcessCounter()));
    }
}

void AScheduler::startSpawning() {
    this->isSpawning = true;
}

void AScheduler::stopSpawning() {
    this->isSpawning = false;
}

void AScheduler::stop() {
    this->running = false;
}


