#include "FCFSScheduler.h"

#include <iostream>
#include <mutex>
#include "../cpu/CPUManager.h"
#include "../cpu/CPUWorker.h"
#include "../console/ConsoleManager.h"

FCFSScheduler::FCFSScheduler(std::shared_ptr<IMemoryAllocator> memoryAllocator) : AScheduler(FCFS, memoryAllocator) {
    
}

void FCFSScheduler::init() {
    // Empty
}

void FCFSScheduler::execute() {
    //if (!this->readyQueue.empty()) {
    //    Process &currentProcess = this->readyQueue.front();
    //    std::cout << "Executing process: " << currentProcess.getName() << std::endl;

    //    // Simulate process execution
    //    currentProcess.setState(Process::RUNNING);
    //    while (currentProcess.getCurrentInstructionLine() < currentProcess.getMaxInstructionLine()) {
    //        // Simulate instruction execution
    //        currentProcess.executeCurrentInstruction();
    //    }
    //    currentProcess.setState(Process::FINISHED);

    //    std::cout << "Finished process: " << currentProcess.getName() << std::endl;

    //    // Remove the process from the queue
    //    this->readyQueue.erase(this->readyQueue.begin());
    //} else {
    //    std::cout << "No more processes to execute." << std::endl;
    //    this->stop();
    //}

    std::vector<CPUWorker*> cores = CPUManager::getInstance()->getCores();
    CPUWorker* currentCore;
    int coreId;

    for (auto it = cores.begin(); it != cores.end(); it++) {
        currentCore = *it;
        coreId = std::distance(cores.begin(), it);
        std::shared_ptr<Process> runningProcess = currentCore->getProcess();

        if (runningProcess != nullptr && runningProcess->isFinished()) {
            // Remove it from CPU
            // Put it in finished list
            // Set state to finished
            // Unregister from console manager
            runningProcess->setState(Process::FINISHED);
            ConsoleManager::getInstance()->unregisterScreen(runningProcess->getName());
            if (!this->assignQueuedProcess(currentCore, coreId)) {
                currentCore->assignProcess(nullptr);
            }
        }

        if (!runningProcess) {
            //std::cout << "CPU " << std::distance(cores.begin(), it) << " is idle. ";
            // CPU is idle; Is ready queue empty?
            // If no,
                // Assign process to core
                // Set state to running
               
            //std::unique_lock<std::mutex> queueLock(this->queueMutex);
            
            this->assignQueuedProcess(currentCore, coreId);
            //lock.unlock();
            //std::cout << "\n";
        }
    }
}
