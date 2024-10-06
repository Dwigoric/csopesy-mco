#ifndef SCREENCOMMAND_H
#define SCREENCOMMAND_H

#include <vector>
#include <string>

#include "ACommand.h"

#include "../process/Process.h"

class ScreenCommand : public ACommand {
public:
    static void execute(std::vector<std::string> parameters, std::vector<Process>& processes);

private:
    static void displayProcesses(std::vector<Process>& processes);
};

#endif //SCREENCOMMAND_H
