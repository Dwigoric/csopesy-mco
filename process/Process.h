//
// Created by Graham Joshua Ogatia on 9/26/24.
//

#ifndef PROCESS_H
#define PROCESS_H
#include <string>


class Process {

public:
    Process(int id, std::string name);
    ~Process() = default;
    std::string getName();
    std::string getCore();
    int getCurrentInstructionLine() const;
    int getMaxInstructionLine() const;

private:
    int id;
    std::string name;
    std::string core = "N/A";
    int currentInstructionLine = 0;
    int maxInstructionLine = 50;
};



#endif //PROCESS_H
