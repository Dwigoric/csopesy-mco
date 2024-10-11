#include "AScheduler.h"

AScheduler::AScheduler(SchedulingAlgorithm algorithm) {
    this->algorithm = algorithm;
}

void AScheduler::scheduleProcess(Process process) {
    this->readyQueue.push_back(process);
    process.setState(Process::READY);
}

void AScheduler::run() {
    this->running = true;
    init();
    while (this->running) {
        execute();
    }
}

void AScheduler::stop() {
    this->running = false;
}


