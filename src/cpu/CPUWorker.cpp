#include "CPUWorker.h"
#include <iostream>

int CPUWorker::delayPerExec = 0;

void CPUWorker::assignProcess(std::shared_ptr<Process> queuedProcess) {
    std::unique_lock<std::mutex> lock(this->mutex);

    this->runningProcess = queuedProcess;
}

std::shared_ptr<Process> CPUWorker::getProcess() const {
    return this->runningProcess;
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

        if (this->cycles++ % (delayPerExec + 1) ==  0) {
            if (this->runningProcess != nullptr) {
                if (!this->runningProcess->isFinished()) {
                    this->runningProcess->executeCurrentInstruction();
                }
            }
        }
    }
}