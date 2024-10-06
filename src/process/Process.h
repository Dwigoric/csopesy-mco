//
// Created by Graham Joshua Ogatia on 9/26/24.
//

#ifndef PROCESS_H
#define PROCESS_H


#include <string>
#include <chrono>

class Process {
public:
    enum ProcessState {
        READY,
        RUNNING,
        WAITING,
        FINISHED,
    };

    Process(int id, std::string name, int maxInstructionLine);

    ~Process() = default;

    void incrementInstructionLine();

    void setState(ProcessState state);

    std::string getName();

    std::string getCore();

    [[nodiscard]] int getCurrentInstructionLine() const;

    [[nodiscard]] int getMaxInstructionLine() const;

    [[nodiscard]] int getId() const;

    [[nodiscard]] std::chrono::system_clock::time_point getTimeCreated() const;

private:
    int id;
    std::string name;
    std::string core = "N/A";
    int currentInstructionLine = 0;
    int maxInstructionLine;
    std::chrono::system_clock::time_point timeCreated;
    ProcessState state = READY;
};


#endif //PROCESS_H
