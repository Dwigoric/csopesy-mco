#include "FCFSScheduler.h"

#include <iostream>

FCFSScheduler::FCFSScheduler() : AScheduler(FCFS) {
}

void FCFSScheduler::init() {
    // TODO: Replace dummy processes with real ones
    this->processes = {
        Process(1, "example_1", 10),
        Process(2, "example_2", 20),
        Process(3, "example_3", 30),
        Process(4, "example_4", 40),
        Process(5, "example_5", 50),
    };
}

void FCFSScheduler::execute() {
    if (!this->processes.empty()) {
        Process &currentProcess = this->processes.front();
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
        this->processes.erase(this->processes.begin());
    } else {
        std::cout << "No more processes to execute." << std::endl;
        this->stop();
    }
}
