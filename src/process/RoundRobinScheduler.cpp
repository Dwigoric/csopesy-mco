#include "RoundRobinScheduler.h"

#include <iostream>
#include <mutex>
#include "../cpu/CPUManager.h"
#include "../cpu/CPUWorker.h"
#include "../console/ConsoleManager.h"

#include <fstream>
#include "../memory/MemoryManager.h"

RoundRobinScheduler::RoundRobinScheduler(int quantum, std::shared_ptr<IMemoryAllocator> memoryAllocator) : AScheduler(ROUND_ROBIN, memoryAllocator) {
    this->quantum = quantum;
}

void RoundRobinScheduler::init() {
    // Empty
}

void RoundRobinScheduler::execute() {
    std::vector<CPUWorker*> cores = CPUManager::getInstance()->getCores();
    CPUWorker* currentCore;
    int coreId;

    for (auto it = cores.begin(); it != cores.end(); it++) {
        currentCore = *it;
        coreId = std::distance(cores.begin(), it);
    	std::shared_ptr<Process> runningProcess = currentCore->getProcess();

        if (runningProcess) {
            // Current running process has finished
            // Deallocate process from memory
            if (runningProcess->isFinished()) {
                runningProcess->setState(Process::FINISHED);
                ConsoleManager::getInstance()->unregisterScreen(runningProcess->getName());
                this->memoryAllocator->deallocate(runningProcess->getId());
                if (!this->assignQueuedProcess(currentCore, coreId)) {
                    currentCore->assignProcess(nullptr);
                }
            }

            // Current quantum timeslice has finished
            // TODO: Put process in backing store
            else if (currentCore->getProcessCycles() >= this->quantum) {
                runningProcess->setState(Process::READY);
                this->readyQueue.push_back(runningProcess);
                if (!this->assignQueuedProcess(currentCore, coreId)) {
                    currentCore->assignProcess(nullptr);
                }
            }
        }

        // Assign a new process to core
        if (!runningProcess) {
            this->assignQueuedProcess(currentCore, coreId);
        }
    }
}
