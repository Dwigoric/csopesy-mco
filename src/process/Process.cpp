//
// Created by Graham Joshua Ogatia on 9/26/24.
//

#include "Process.h"

#include <utility>

Process::Process(int id, std::string name, int maxInstructionLine) {
    this->id = id;
    this->name = std::move(name);
    this->timeCreated = std::chrono::system_clock::now();
    this->maxInstructionLine = maxInstructionLine;
}

void Process::executeCurrentInstruction() {
    this->currentInstructionLine++;
}

void Process::setState(const ProcessState state) {
    this->state = state;
}

std::string Process::getName() {
    return this->name;
}

std::string Process::getCore() {
    return this->core;
}

int Process::getCurrentInstructionLine() const {
    return this->currentInstructionLine;
}

int Process::getMaxInstructionLine() const {
    return this->maxInstructionLine;
}

int Process::getId() const {
    return this->id;
}

std::chrono::system_clock::time_point Process::getTimeCreated() const {
    return this->timeCreated;
}
