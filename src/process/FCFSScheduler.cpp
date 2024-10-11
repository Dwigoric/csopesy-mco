#include "FCFSScheduler.h"

#include <iostream>

FCFSScheduler::FCFSScheduler() : AScheduler(FCFS) {
    
}

void FCFSScheduler::init() {
    // Empty
}

void FCFSScheduler::execute() {
    if (!this->readyQueue.empty()) {
        Process &currentProcess = this->readyQueue.front();
        std::cout << "Executing process: " << currentProcess.getName() << std::endl;

        // Simulate process execution
        currentProcess.setState(Process::RUNNING);
        while (currentProcess.getCurrentInstructionLine() < currentProcess.getMaxInstructionLine()) {
            // Simulate instruction execution
            currentProcess.executeCurrentInstruction();
        }
        currentProcess.setState(Process::FINISHED);

        std::cout << "Finished process: " << currentProcess.getName() << std::endl;

        // Remove the process from the queue
        this->readyQueue.erase(this->readyQueue.begin());
    } else {
        std::cout << "No more processes to execute." << std::endl;
        this->stop();
    }
}
