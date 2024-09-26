//
// Created by Graham Joshua Ogatia on 9/26/24.
//

#include "Process.h"

Process::Process(int id, std::string name) {
    this->id = id;
    this->name = name;
}

std::string Process::getName() {
    return this->name;
}

int Process::getCurrentInstructionLine() const {
    return this->currentInstructionLine;
}

int Process::getMaxInstructionLine() const {
    return this->maxInstructionLine;
}
