//
// Created by Graham Joshua Ogatia on 9/26/24.
//

#ifndef PROCESS_H
#define PROCESS_H


#include <string>
#include <chrono>

#include "../instructions/AInstruction.h"

class Process {
public:
    enum ProcessState {
        READY,
        RUNNING,
        WAITING,
        FINISHED,
    };

    Process(int id, std::string name, size_t memoryRequired);

    void addCommand(AInstruction::InstructionType instructionType);

    void executeCurrentInstruction();

    [[nodiscard]] bool isFinished() const;

    void setState(ProcessState state);

    void setCore(int core);

    std::string getName();

    int getCore();

    [[nodiscard]] ProcessState getState();

    [[nodiscard]] int getCurrentInstructionLine() const;

    [[nodiscard]] int getMaxInstructionLine() const;

    [[nodiscard]] int getId() const;

    [[nodiscard]] std::chrono::system_clock::time_point getTimeCreated() const;

    [[nodiscard]] std::chrono::system_clock::time_point getTimeExecuted() const;

    void setTimeExecuted();

    static size_t memPerProc;

private:
    int id;
    std::string name;
    int core = -1;
    int currentInstructionLine = 0;
    std::chrono::system_clock::time_point timeCreated;
    std::chrono::system_clock::time_point timeExecuted;
    ProcessState state = READY;
    std::vector<std::shared_ptr<AInstruction> > instructionList;
    size_t memoryRequired;

    // TEMP: For Homework 6 Only
    std::string outfile;
};


#endif //PROCESS_H
