#include "CPUWorker.h"
#include <iostream>

int CPUWorker::delayPerExec = 0;

void CPUWorker::assignProcess(std::shared_ptr<Process> queuedProcess) {
    std::unique_lock<std::mutex> lock(this->mutex);

    this->runningProcess = queuedProcess;
    this->processCycles = 0;
}

std::shared_ptr<Process> CPUWorker::getProcess() const {
    return this->runningProcess;
}

int CPUWorker::getProcessCycles() const {
    return this->processCycles;
}


void CPUWorker::start() {
    this->isRunning = true;
    Thread::start();
}

void CPUWorker::stop() {
    this->isRunning = false;
}

void CPUWorker::run() {
    while (isRunning) {
    	std::unique_lock<std::mutex> lock(this->mutex);

        this->processCycles++;
        if (this->cycles++ % (delayPerExec + 1) ==  0) {
            if (this->runningProcess != nullptr) {
                if (!this->runningProcess->isFinished()) {
                    this->runningProcess->executeCurrentInstruction();
                }
            }
        }
    }
}

