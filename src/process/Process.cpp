//
// Created by Graham Joshua Ogatia on 9/26/24.
//

#include "Process.h"

#include <utility>
#include <fstream>
#include <cmath>

#include "AScheduler.h"
#include "../instructions/PrintInstruction.h"
#include "../threading/SchedulerThread.h"
#include "../instructions/NoOpInstruction.h"

//size_t Process::memPerProc = 0;
size_t Process::minMemPerProc = 1;
size_t Process::maxMemPerProc = 1;
size_t Process::pageSize = 1;

Process::Process(const int id, std::string name, size_t memoryRequired) {
    this->id = id;
    this->name = std::move(name);
    this->memoryRequired = memoryRequired;

    this->numPages = ceil(static_cast<float>(memoryRequired) / static_cast<float>(pageSize));

    this->timeCreated = std::chrono::system_clock::now();

    this->outfile = this->name + "_log.txt";

    // std::ofstream fs(this->outfile);
    // fs << "Process name: " << this->name << "\nLog:\n\n";
    // fs.close();
}

void Process::addCommand(AInstruction::InstructionType instructionType) {
    std::shared_ptr<AInstruction> instruction;

    if (instructionType == AInstruction::PRINT) {
        std::string toPrint = "Hello world from " + this->name + "!";
        instruction = std::make_shared<PrintInstruction>(this->id, toPrint, this->outfile);
    }
    else if (instructionType == AInstruction::NOOP) {
        instruction = std::make_shared<NoOpInstruction>();
    }

    this->instructionList.push_back(instruction);
}

void Process::executeCurrentInstruction() {
    // TEMP: execute should get core information
    this->instructionList[this->currentInstructionLine]->execute(this->core);
    this->currentInstructionLine++; // not sure if needed to put in separate function moveToNextLine()?
}

bool Process::isFinished() const {
    return this->currentInstructionLine == this->instructionList.size();
}

void Process::setState(const ProcessState state) {
    this->state = state;
}

void Process::setCore(int core) {
    this->core = core;
}

std::string Process::getName() {
    return this->name;
}

int Process::getCore() {
    return this->core;
}

Process::ProcessState Process::getState() {
    return this->state;
}

int Process::getCurrentInstructionLine() const {
    return this->currentInstructionLine;
}

int Process::getMaxInstructionLine() const {
    return this->instructionList.size();
}

int Process::getId() const {
    return this->id;
}

std::chrono::system_clock::time_point Process::getTimeCreated() const {
    return this->timeCreated;
}

std::chrono::system_clock::time_point Process::getTimeExecuted() const {
    return this->timeExecuted;
}

void Process::setTimeExecuted() {
	this->timeExecuted = std::chrono::system_clock::now();
}

size_t Process::getMemoryRequired() {
    return this->memoryRequired;
}

size_t Process::getNumPages() {
    return this->numPages;
}


std::vector<size_t> Process::getPageSizes() {
    //TODO: Implement Get Page Sizes
    std::vector<size_t> examplePageSizes = {4096, 8192, 16384};
    return examplePageSizes;
}

bool Process::isInMemory() {
    return this->inMemory;
}

void Process::setInMemory(bool inMemory) {
    this->inMemory = inMemory;
}
