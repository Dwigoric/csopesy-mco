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

    size_t getMemoryRequired();

    bool isInMemory();

    void setInMemory(bool inMemory);

    // Example page sizes in bytes (e.g., 4KB, 8KB, 16KB)
    std::vector<size_t> getPageSizes();
    size_t getNumPages();

    //static size_t memPerProc;
    static size_t minMemPerProc;
    static size_t maxMemPerProc;
    static size_t pageSize;

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
    size_t numPages;
    bool inMemory = false;

    // TEMP: For Homework 6 Only
    std::string outfile;
};


#endif //PROCESS_H
