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

    Process(int id, std::string name);

    ~Process() = default;

    std::string getName();

    std::string getCore();

    int getCurrentInstructionLine() const;

    int getMaxInstructionLine() const;

    int getId() const;

    std::chrono::system_clock::time_point getTimeCreated() const;

private:
    int id;
    std::string name;
    std::string core = "N/A";
    int currentInstructionLine = 0;
    int maxInstructionLine = 50;
    std::chrono::system_clock::time_point timeCreated;
};

#endif //PROCESS_H
