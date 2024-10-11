#include "FCFSScheduler.h"

#include <iostream>
#include <mutex>
#include "../cpu/CPUManager.h"
#include "../cpu/CPUWorker.h"

FCFSScheduler::FCFSScheduler() : AScheduler(FCFS) {
    
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

    for (auto it = cores.begin(); it != cores.end(); it++) {
        currentCore = *it;
        std::shared_ptr<Process> runningProcess = currentCore->getProcess();

        if (runningProcess != nullptr && runningProcess->isFinished()) {
            // Remove it from CPU
            // Put it in finished list
            // Set state to finished
            runningProcess->setState(Process::FINISHED);
            currentCore->assignProcess(nullptr);
        }

        if (!runningProcess) {
            //std::cout << "CPU " << std::distance(cores.begin(), it) << " is idle. ";
            // CPU is idle; Is ready queue empty?
            // If no,
                // Assign process to core
                // Set state to running
               
            //std::unique_lock<std::mutex> queueLock(this->queueMutex);
            
            if (!this->readyQueue.empty()) {
                //std::cout << "Queueing process!";
                std::shared_ptr<Process> nextProcess = this->readyQueue.front();
                this->readyQueue.erase(this->readyQueue.begin());

                nextProcess->setCore(std::distance(cores.begin(), it));
                nextProcess->setState(Process::RUNNING);
                nextProcess->setTimeExecuted();
                currentCore->assignProcess(nextProcess);
            }
            else {
                //std::cout << "Ready queue is empty!";
            }
            //lock.unlock();
            //std::cout << "\n";
        }
    }
}
