#include "RoundRobinScheduler.h"

#include <iostream>
#include <mutex>
#include "../cpu/CPUManager.h"
#include "../cpu/CPUWorker.h"
#include "../console/ConsoleManager.h"

RoundRobinScheduler::RoundRobinScheduler(int quantum) : AScheduler(ROUND_ROBIN) {
    this->quantum = quantum;
}

void RoundRobinScheduler::init() {
    // Empty
}

void RoundRobinScheduler::execute() {
    std::vector<CPUWorker*> cores = CPUManager::getInstance()->getCores();
    CPUWorker* currentCore;

    for (auto it = cores.begin(); it != cores.end(); it++) {
        currentCore = *it;
        std::shared_ptr<Process> runningProcess = currentCore->getProcess();

        if (runningProcess) {
            // Current running process has finished
            if (runningProcess->isFinished()) {
                runningProcess->setState(Process::FINISHED);
                ConsoleManager::getInstance()->unregisterScreen(runningProcess->getName());
                if (!this->readyQueue.empty()) {
                    std::shared_ptr<Process> nextProcess = this->readyQueue.front();
                    this->readyQueue.erase(this->readyQueue.begin());

                    nextProcess->setCore(std::distance(cores.begin(), it));
                    nextProcess->setState(Process::RUNNING);
                    nextProcess->setTimeExecuted();
                    currentCore->assignProcess(nextProcess);
                }
                else {
                    currentCore->assignProcess(nullptr);
                }
            }

            // Current quantum timeslice has finished
            else if (currentCore->getProcessCycles() >= this->quantum) {
                runningProcess->setState(Process::READY);
                this->readyQueue.push_back(runningProcess);
                if (!this->readyQueue.empty()) {
                    std::shared_ptr<Process> nextProcess = this->readyQueue.front();
                    this->readyQueue.erase(this->readyQueue.begin());

                    nextProcess->setCore(std::distance(cores.begin(), it));
                    nextProcess->setState(Process::RUNNING);
                    nextProcess->setTimeExecuted();
                    currentCore->assignProcess(nextProcess);
                }
                else {
                    currentCore->assignProcess(nullptr);
                }
            }
        }

        // Assign a new process to core
        if (!runningProcess && !this->readyQueue.empty()) {
            std::shared_ptr<Process> nextProcess = this->readyQueue.front();
            this->readyQueue.erase(this->readyQueue.begin());

            nextProcess->setCore(std::distance(cores.begin(), it));
            nextProcess->setState(Process::RUNNING);
            nextProcess->setTimeExecuted();
            currentCore->assignProcess(nextProcess);
        }
    }
}
