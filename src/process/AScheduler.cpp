#include "AScheduler.h"

#include "../console/ConsoleManager.h"
#include "../threading/SchedulerThread.h"

AScheduler::AScheduler(const SchedulingAlgorithm algorithm, std::shared_ptr<IMemoryAllocator> memoryAllocator) {
    this->algorithm = algorithm;
    this->memoryAllocator = memoryAllocator;
    this->spawnFrequency = std::stoi(ConsoleManager::getInstance()->getConfigs().at("batch-process-freq"));
}

void AScheduler::scheduleProcess(const std::shared_ptr<Process> &process) {
    this->readyQueue.push_back(process);
    process->setState(Process::READY);
}

bool AScheduler::assignQueuedProcess(CPUWorker* core, int coreId) {
    if (!this->readyQueue.empty()) {
        std::shared_ptr<Process> nextProcess = this->readyQueue.front();
        this->readyQueue.erase(this->readyQueue.begin());

        // Only assign if enough space to allocate
        if (this->memoryAllocator->allocate(nextProcess->getId(), nextProcess->getMemoryRequired()) != nullptr) {
            nextProcess->setCore(coreId);
            nextProcess->setState(Process::RUNNING);
            nextProcess->setTimeExecuted();
            core->assignProcess(nextProcess);

            return true;
        }

        // No space, re-queue process
        this->readyQueue.push_back(nextProcess);
    }

    return false;
}

void AScheduler::run() {
    this->running = true;
    init();
    while (this->running) {
        onTick();
        execute();
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
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


