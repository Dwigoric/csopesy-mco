//
// Created by Graham Joshua Ogatia on 9/26/24.
//

#include "Process.h"

#include <utility>
#include <fstream>

#include "../instructions/PrintInstruction.h"

Process::Process(int id, std::string name) {
    this->id = id;
    this->name = std::move(name);
    this->timeCreated = std::chrono::system_clock::now();

    this->outfile = name + "_log.txt";
}

void Process::addCommand(AInstruction::InstructionType instructionType) {
    std::shared_ptr<AInstruction> instruction;

	if (instructionType == AInstruction::PRINT) {
        std::string toPrint = "This is a sample print.";
        instruction = std::make_shared<PrintInstruction>(this->id, toPrint, this->outfile);
	}

    this->instructionList.push_back(instruction);
}

void Process::executeCurrentInstruction() {
    // TEMP: execute should get core information
    this->instructionList[this->currentInstructionLine]->execute(0);
    this->currentInstructionLine++; // not sure if needed to put in separate function moveToNextLine()?
}

bool Process::isFinished() const {
    return this->currentInstructionLine == this->instructionList.size();
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
    return this->instructionList.size();
}

int Process::getId() const {
    return this->id;
}

std::chrono::system_clock::time_point Process::getTimeCreated() const {
    return this->timeCreated;
}
