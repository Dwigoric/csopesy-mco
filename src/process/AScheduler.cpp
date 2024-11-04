#include "AScheduler.h"

#include "../console/ConsoleManager.h"
#include "../threading/SchedulerThread.h"

AScheduler::AScheduler(const SchedulingAlgorithm algorithm) {
    this->algorithm = algorithm;
    this->spawnFrequency = std::stoi(ConsoleManager::getInstance()->getConfigs().at("batch-process-freq"));
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

void AScheduler::onTick() {
    if (this->isSpawning && this->spawnCounter >= this->spawnFrequency) {
        SchedulerThread::getInstance()->createProcess(
            std::format("process_{}", SchedulerThread::getInstance()->getProcessCounter()));

        this->spawnCounter = 0;
    } else {
        this->spawnCounter++;
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


